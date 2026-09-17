#include "PreeditWindow.h"

bool PreeditWindow::RegisterWindowClass(HINSTANCE hInstance)
{
    static bool registered = false;

    if (registered)
    {
        return true;
    }

    WNDCLASSW wc{};

    wc.lpfnWndProc = &PreeditWindow::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = nullptr;

    if (!RegisterClassW(&wc))
    {
        if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        {
            return false;
        }
    }

    registered = true;
    return true;
}

bool PreeditWindow::Create(HWND hParent, HINSTANCE hInstance)
{
    if (m_hWnd)
    {
        return true;
    }

    if (!RegisterWindowClass(hInstance))
    {
        return false;
    }

    m_hInstance = hInstance;

    m_hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"",
        WS_CHILD | WS_VISIBLE,
        0, 0,
        300, 30,
        hParent,
        nullptr,
        hInstance,
        this
    );

    return m_hWnd != nullptr;
}

void PreeditWindow::Destroy()
{
    if (m_hWnd)
    {
        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }

    if (m_hFont)
    {
        DeleteObject(m_hFont);
        m_hFont = nullptr;
    }
}

PreeditWindow::~PreeditWindow()
{
    Destroy();
}

void PreeditWindow::Show()
{
    if (m_hWnd)
    {
        ShowWindow(m_hWnd, SW_SHOW);
    }
}

void PreeditWindow::Hide()
{
    if (m_hWnd)
    {
        ShowWindow(m_hWnd, SW_HIDE);
    }
}

void PreeditWindow::SetText(const std::wstring& text)
{
    m_text = text;

    if (m_hWnd)
    {
        InvalidateRect(m_hWnd, nullptr, TRUE);
    }
}

bool PreeditWindow::CreateFont(
    int height,
    int weight,
    const wchar_t* fontName
)
{
    HFONT hFont = ::CreateFontW(
        height,
        0,
        0,
        0,
        weight,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        fontName
    );

    if (!hFont)
    {
        return false;
    }

    if (m_hFont)
    {
        DeleteObject(m_hFont);
    }

    m_hFont = hFont;

    if (m_hWnd)
    {
        InvalidateRect(m_hWnd, nullptr, TRUE);
    }

    return true;
}

void PreeditWindow::SetWindowTextColor(COLORREF color)
{
    m_textColor = color;

    if (m_hWnd)
    {
        InvalidateRect(m_hWnd, nullptr, TRUE);
    }
}

void PreeditWindow::SetBackgroundColor(COLORREF color)
{
    m_backgroundColor = color;

    if (m_hWnd)
    {
        InvalidateRect(m_hWnd, nullptr, TRUE);
    }
}

void PreeditWindow::SetBounds(
    int x,
    int y,
    int width,
    int height
)
{
    if (!m_hWnd)
    {
        return;
    }

    SetWindowPos(
        m_hWnd,
        nullptr,
        x, y,
        width, height,
        SWP_NOZORDER | SWP_NOACTIVATE
    );
}

HWND PreeditWindow::GetHandle() const
{
    return m_hWnd;
}

LRESULT CALLBACK PreeditWindow::WndProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    PreeditWindow* pThis = nullptr;

    if (message == WM_NCCREATE)
    {
        auto* createStruct =
            reinterpret_cast<CREATESTRUCTW*>(lParam);

        pThis = static_cast<PreeditWindow*>(
            createStruct->lpCreateParams
        );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pThis)
        );

        pThis->m_hWnd = hwnd;
    }
    else
    {
        pThis = reinterpret_cast<PreeditWindow*>(
            GetWindowLongPtrW(hwnd, GWLP_USERDATA)
        );
    }

    if (pThis)
    {
        return pThis->HandleMessage(
            hwnd,
            message,
            wParam,
            lParam
        );
    }

    return DefWindowProcW(
        hwnd,
        message,
        wParam,
        lParam
    );
}

LRESULT PreeditWindow::HandleMessage(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (message)
    {
    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_ERASEBKGND:
        return 1;

    case WM_NCDESTROY:
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);
        m_hWnd = nullptr;
        break;
    }

    return DefWindowProcW(
        hwnd,
        message,
        wParam,
        lParam
    );
}

void PreeditWindow::OnPaint()
{
    PAINTSTRUCT ps{};

    HDC hdc = BeginPaint(m_hWnd, &ps);

    RECT rect{};
    GetClientRect(m_hWnd, &rect);

    // 绘制背景
    HBRUSH hBrush = CreateSolidBrush(m_backgroundColor);

    FillRect(hdc, &rect, hBrush);

    DeleteObject(hBrush);

    // 设置字体
    HFONT hOldFont = nullptr;

    if (m_hFont)
    {
        hOldFont = static_cast<HFONT>(
            SelectObject(hdc, m_hFont)
        );
    }

    // 设置文字颜色
    SetTextColor(hdc, m_textColor);
    SetBkMode(hdc, TRANSPARENT);

    // 绘制文字
    DrawTextW(
        hdc,
        m_text.c_str(),
        static_cast<int>(m_text.size()),
        &rect,
        DT_LEFT |
        DT_VCENTER |
        DT_SINGLELINE |
        DT_NOPREFIX
    );

    // 恢复 DC 原来的字体
    if (hOldFont)
    {
        SelectObject(hdc, hOldFont);
    }

    EndPaint(m_hWnd, &ps);
}
