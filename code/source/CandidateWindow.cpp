#include "CandidateWindow.h"
#include "ICandidateView.h"

#include <stdexcept>

namespace
{
    const wchar_t* WindowClassName = L"CandidateWindowClass";
}

CandidateWindow::CandidateWindow(
    std::unique_ptr<ICandidateView> view)
    : m_view(std::move(view))
{
}

CandidateWindow::~CandidateWindow()
{
    if (m_hwnd != nullptr)
    {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
}

bool CandidateWindow::Create(HINSTANCE hInstance)
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

    m_hwnd = CreateWindowEx(
        WS_EX_TOOLWINDOW,
        WindowClassName,
        L"Candidate Window",
        WS_POPUP,
        100,
        100,
        300,
        200,
        nullptr,
        nullptr,
        m_hInstance,
        this);

    if (m_hwnd == nullptr)
    {
        return false;
    }

    if(m_view !=nullptr)
    {
        if (!m_view->Create(m_hwnd))
        {
            DestroyWindow(m_hwnd);
            m_hwnd = nullptr;
            return false;
        }
	}
    return true;
}

void CandidateWindow::Hide()
{
    if (m_hwnd == nullptr)
        return;

    if (m_view)
    {
        m_view->Resize(0, 0);
    }
    ShowWindow(m_hwnd, SW_HIDE);
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

        window->m_hwnd = hwnd;
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
        if (m_view)
        {
            if (!m_view->Create(m_hwnd))
            {
                return -1;
            }
        }

        return 0;
    }

    case WM_SIZE:
    {
        const int width = LOWORD(lParam);
        const int height = HIWORD(lParam);

        if (m_view)
        {
            m_view->Resize(width, height);
        }

        return 0;
    }

    case WM_CLOSE:
    {
        DestroyWindow(m_hwnd);
        return 0;
    }

    case WM_DESTROY:
    {
        m_hwnd = nullptr;
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProc(
        m_hwnd,
        message,
        wParam,
        lParam);
}

void CandidateWindow::Show()
{
    if (m_view)
    {
        m_view->Resize(300,200);
    }
    ShowWindow(m_hwnd, SW_SHOW);
}


void CandidateWindow::Move(int x, int y)
{
    SetWindowPos(
        m_hwnd,
        HWND_TOPMOST,
        x,
        y,
        300,
        200,
        SWP_SHOWWINDOW);

    if (m_view)
    {
        m_view->Resize(300, 200);
    }
}

void CandidateWindow::SetCandidates(
    const std::vector<std::wstring>& candidates)
{
    if (m_view)
    {
		m_view->SetCandidates(candidates);
    }
}

int CandidateWindow::GetSelectedIndex() const
{
    return 0;
}

void CandidateWindow::SetSelectedIndex(int index)
{
    if (m_view)
    {
		m_view->SetSelectedIndex(index);
    }
}

HWND CandidateWindow::GetHandle() const
{
    return m_hwnd;
}
