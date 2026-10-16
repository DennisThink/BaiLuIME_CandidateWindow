#include "TestWindow.h"
#include "ListCandidateView.h"
#include "CommonFunction.h"
TestWindow::TestWindow()
{
    m_candidateSets =
    {
        {
            u8"你好",
            u8"你号",
            u8"拟好",
            u8"泥好"
        },

        {
            u8"中国",
            u8"中华",
            u8"中午",
            u8"中央"
        },

        {
            u8"深圳",
            u8"深夜",
            u8"申请",
            u8"身边",
            u8"审判"
        }
    };
}

TestWindow::~TestWindow()
{
}

bool TestWindow::Create(HINSTANCE hInstance)
{
    m_hInstance = hInstance;

    const char CLASS_NAME[] =
        "CandidateWindowTest";

    WNDCLASSA wc = {};
    wc.lpfnWndProc = TestWindow::WndProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorA(
        nullptr,
        IDC_ARROW);

    if (!RegisterClassA(&wc))
    {
        if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        {
            return false;
        }
    }

    m_hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "CandidateWindow Test",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        700,
        450,
        nullptr,
        nullptr,
        m_hInstance,
        this);

	//m_candidateWindow.Create(m_hwnd,hInstance);
    if (m_hwnd == nullptr)
    {
        return false;
    }

    return true;
}

int TestWindow::Run()
{
    ShowWindow(
        m_hwnd,
        SW_SHOW);

    UpdateWindow(m_hwnd);

    MSG msg = {};

    while (GetMessageW(
        &msg,
        nullptr,
        0,
        0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK TestWindow::WndProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    TestWindow* self =
        reinterpret_cast<TestWindow*>(
            GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA));

    if (message == WM_NCCREATE)
    {
        auto* createStruct =
            reinterpret_cast<CREATESTRUCTW*>(
                lParam);

        self =
            static_cast<TestWindow*>(
                createStruct->lpCreateParams);

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(self));

        self->m_hwnd = hwnd;
    }

    if (self != nullptr)
    {
        return self->HandleMessage(
            message,
            wParam,
            lParam);
    }

    return DefWindowProcW(
        hwnd,
        message,
        wParam,
        lParam);
}

LRESULT TestWindow::HandleMessage(
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        OnCreate();
        return 0;

    case WM_KEYDOWN:
        OnKeyDown(wParam);
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_SIZE:
        OnSize(
            LOWORD(lParam),
            HIWORD(lParam));
        return 0;

    case WM_DESTROY:
        OnDestroy();
        return 0;
    }

    return DefWindowProcW(
        m_hwnd,
        message,
        wParam,
        lParam);
}

void TestWindow::OnCreate()
{
    if (m_candidateSets.empty())
    {
        return;
    }

    m_candidateSetIndex = 0;

    m_core.SetCandidates(
        m_candidateSets[m_candidateSetIndex]);

    //m_candidateWindow.Move(
    //    100,
    //    100);

    //m_candidateWindow.Show();

    UpdateStatus();
}

void TestWindow::OnKeyDown(WPARAM key)
{
    // X: TestWindow 自己处理，
    // 用来切换测试数据。
    if (key == 'X' || key == 'x')
    {
        SwitchCandidateSet();
        return;
    }

    // 其他按键交给 TestCore。
    m_core.OnKeyDown(key);

    // 如果 Core 判断输入已经结束，
    // TestWindow 获取最终选择。
    if (m_core.IsInputFinished())
    {
        m_lastCommitted =
            m_core.GetSelectedCandidate();

        OutputDebugStringW(
            L"Input finished: ");

        OutputDebugStringA(
            m_lastCommitted.c_str());

        OutputDebugStringW(L"\n");

        UpdateStatus();

        return;
    }

    UpdateStatus();
}

void TestWindow::OnPaint()
{
    PAINTSTRUCT ps = {};

    HDC hdc = BeginPaint(
        m_hwnd,
        &ps);

    RECT clientRect = {};

    GetClientRect(
        m_hwnd,
        &clientRect);

    int x = 30;
    int y = 30;

    std::wstring text;

    text =
        L"CandidateWindow Test";

    TextOutW(
        hdc,
        x,
        y,
        text.c_str(),
        static_cast<int>(text.length()));

    y += 40;

    text =
        L"Candidate set: " +
        std::to_wstring(
            m_candidateSetIndex + 1);

    TextOutW(
        hdc,
        x,
        y,
        text.c_str(),
        static_cast<int>(text.length()));

    y += 30;

    text =
        L"Selected index: " +
        std::to_wstring(
            m_core.GetSelectedIndex());

    TextOutW(
        hdc,
        x,
        y,
        text.c_str(),
        static_cast<int>(text.length()));

    y += 30;

    text =
        L"Input finished: " +
        std::wstring(
            m_core.IsInputFinished()
                ? L"yes"
                : L"no");

    TextOutW(
        hdc,
        x,
        y,
        text.c_str(),
        static_cast<int>(text.length()));

    y += 30;

    {
        std::string text1;
        if(m_lastCommitted.empty())
        {
            text1 =
                "Last committed: (none)";
        }
        else
        {
            text1 =
                "Last committed: " + m_lastCommitted;
		}
        OutputDebugStringA(text1.c_str());
		text1 += "            ";
		std::wstring wstrLastCommit = Utf8ToUtf16(text1);
        TextOutW(
            hdc,
            x,
            y,
            wstrLastCommit.data(),
            static_cast<int>(wstrLastCommit.size()));
    }

    y += 50;

    text =
        L"[1-9] Select    "
        L"[Up/Down] Move    "
        L"[X] Next set";

    TextOutW(
        hdc,
        x,
        y,
        text.c_str(),
        static_cast<int>(text.length()));

    y += 25;

    text =
        L"[Space] Commit";

    TextOutW(
        hdc,
        x,
        y,
        text.c_str(),
        static_cast<int>(text.length()));

    EndPaint(
        m_hwnd,
        &ps);
}

void TestWindow::OnSize(
    int width,
    int height)
{
    // TestWindow 自己的布局暂时不需要
    // CandidateWindow 跟随 TestWindow。
    //
    // 这里暂时保持 CandidateWindow
    // 作为独立 popup。
    (void)width;
    (void)height;
}

void TestWindow::OnDestroy()
{
    //m_candidateWindow.Hide();

    PostQuitMessage(0);
}

void TestWindow::SwitchCandidateSet()
{
    if (m_candidateSets.empty())
    {
        return;
    }

    ++m_candidateSetIndex;

    if (m_candidateSetIndex >=
        static_cast<int>(m_candidateSets.size()))
    {
        m_candidateSetIndex = 0;
    }

    m_lastCommitted.clear();

    ResetInput();

    m_core.SetCandidates(
        m_candidateSets[m_candidateSetIndex]);
    //m_candidateWindow.Show();

    UpdateStatus();
}

void TestWindow::UpdateStatus()
{
    InvalidateRect(
        m_hwnd,
        nullptr,
        TRUE);
}

void TestWindow::ResetInput()
{
    m_core.ResetInput();
}