#include "CandidateWindow.h"
#include "ICandidateView.h"
#include "PreeditWindow.h"
#include "ListCandidateView.h"
#include <stdexcept>

namespace
{
    const wchar_t* WindowClassName = L"CandidateWindowClass";
}

void CandidateWindow::Destroy()
{

}
CandidateWindow::CandidateWindow()
{
    m_preeditWindow = std::make_unique<PreeditWindow>();
    m_CandidateListWindow = std::make_unique<ListCandidateView>();
}

CandidateWindow::~CandidateWindow()
{
    if (m_hWnd != nullptr)
    {
        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }
}

bool CandidateWindow::Create(HWND hParent, HINSTANCE hInstance)
{
    m_hInstance = hInstance;

    WNDCLASS wc{};
    wc.lpfnWndProc = CandidateWindow::WndProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = WindowClassName;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

    if (RegisterClass(&wc) == 0)
    {
        if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        {
            return false;
        }
    }

    m_hWnd = CreateWindowEx(
        WS_EX_TOOLWINDOW,
        WindowClassName,
        L"Candidate Window",
        WS_POPUP,
        100,
        100,
        300,
        300,
        nullptr,
        nullptr,
        m_hInstance,
        this);

    if (m_hWnd == nullptr)
    {
        return false;
    }

    if(m_CandidateListWindow !=nullptr)
    {
        if (!m_CandidateListWindow->Create(m_hWnd, m_hInstance))
        {
            DestroyWindow(m_hWnd);
            m_hWnd = nullptr;
            return false;
        }
	}
    if (m_preeditWindow != nullptr)
    {
        if (m_preeditWindow->Create(m_hWnd, m_hInstance))
        {

        }
    }
    UpdateLayout();
    return true;
}

LRESULT CALLBACK CandidateWindow::WndProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    CandidateWindow* window = nullptr;

    if (message == WM_NCCREATE)
    {
        auto* createStruct =
            reinterpret_cast<CREATESTRUCT*>(lParam);

        window =
            static_cast<CandidateWindow*>(createStruct->lpCreateParams);

        SetWindowLongPtr(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(window));

        window->m_hWnd = hwnd;
    }
    else
    {
        window =
            reinterpret_cast<CandidateWindow*>(
                GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (window != nullptr)
    {
        return window->HandleMessage(
            message,
            wParam,
            lParam);
    }

    return DefWindowProc(
        hwnd,
        message,
        wParam,
        lParam);
}

LRESULT CandidateWindow::HandleMessage(
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        if (m_CandidateListWindow)
        {
        }

        return 0;
    }

    case WM_SIZE:
    {
        const int width = LOWORD(lParam);
        const int height = HIWORD(lParam);
        return 0;
    }

    case WM_CLOSE:
    {
        DestroyWindow(m_hWnd);
        return 0;
    }

    case WM_DESTROY:
    {
        m_hWnd = nullptr;
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProc(
        m_hWnd,
        message,
        wParam,
        lParam);
}

void CandidateWindow::UpdateLayout()
{
    Show();
    static constexpr int PREEDIT_HEIGHT = 30;
    static constexpr int LIST_WIDTH = 300;
    static constexpr int LIST_HEIGHT = 200;
    if (!m_hWnd)
    {
        return;
    }

    RECT rect{};
    GetClientRect(m_hWnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    const int preeditHeight = 30;

    if (m_preeditWindow != nullptr)
    {
        // PreeditWindow：位于顶部
        if (m_preeditWindow->GetHandle())
        {
            SetWindowPos(
                m_preeditWindow->GetHandle(),
                nullptr,
                0,
                0,
                width,
                preeditHeight,
                SWP_NOZORDER | SWP_NOACTIVATE
            );
        }
        m_preeditWindow->Show();
    }

    // ListBox：位于 PreeditWindow 下方
    if (m_CandidateListWindow)
    {
        SetWindowPos(
            m_CandidateListWindow->GetHandle(),
            nullptr,
            0,
            preeditHeight,
            width,
            height - preeditHeight,
            SWP_NOZORDER | SWP_NOACTIVATE
        );
        m_CandidateListWindow->Show();
    }

}
void CandidateWindow::Move(int x, int y)
{
    SetWindowPos(
        m_hWnd,
        HWND_TOPMOST,
        x,
        y,
        300,
        300,
        SWP_SHOWWINDOW);
    UpdateLayout();
}

void CandidateWindow::SetUserInput(const std::wstring& strUserInput)
{
    if (nullptr != m_preeditWindow)
    {
        m_preeditWindow->SetText(strUserInput);
    }
}

void CandidateWindow::SetCandidates(
    const std::vector<std::wstring>& candidates)
{
    if (m_CandidateListWindow)
    {
        m_CandidateListWindow->SetCandidates(candidates);
    }
    UpdateLayout();
}

int CandidateWindow::GetSelectedIndex() const
{
    return 0;
}

void CandidateWindow::SetSelectedIndex(int index)
{
    if (m_CandidateListWindow)
    {
        m_CandidateListWindow->SetSelectedIndex(index);
    }
}