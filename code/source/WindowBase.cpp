#include "WindowBase.hpp"

void WindowBase::Destroy()
{
    if (m_hWnd)
    {
        ::DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }
}

void WindowBase::Show()
{
    if (!m_hWnd)
        return;

    ::ShowWindow(m_hWnd,SW_SHOW);
}

void WindowBase::Hide()
{
    if (!m_hWnd)
        return;

    ::ShowWindow(m_hWnd, SW_HIDE);
}

void WindowBase::SetPosition(int x, int y)
{
    if (!m_hWnd)
        return;

    ::SetWindowPos(
        m_hWnd,
        nullptr,
        x,
        y,
        0,
        0,
        SWP_NOSIZE |
        SWP_NOZORDER |
        SWP_NOACTIVATE
    );
}

void WindowBase::SetSize(int width, int height)
{
    if (!m_hWnd)
        return;

    ::SetWindowPos(
        m_hWnd,
        nullptr,
        0,
        0,
        width,
        height,
        SWP_NOMOVE |
        SWP_NOZORDER |
        SWP_NOACTIVATE
    );
}

void WindowBase::SetBounds(
    int x,
    int y,
    int width,
    int height)
{
    if (!m_hWnd)
        return;

    ::SetWindowPos(
        m_hWnd,
        nullptr,
        x,
        y,
        width,
        height,
        SWP_NOZORDER |
        SWP_NOACTIVATE
    );
}

HWND WindowBase::GetHandle() const
{
    return m_hWnd;
}