#include "ListCandidateView.h"

ListCandidateView::ListCandidateView()
{
}

ListCandidateView::~ListCandidateView()
{
    if (m_hwnd != nullptr)
    {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
}

bool ListCandidateView::Create(HWND parent)
{
    if (parent == nullptr)
    {
        return false;
    }

    m_hwnd = CreateWindowExW(
        0,
        L"LISTBOX",
        nullptr,
        WS_CHILD |
        WS_VISIBLE |
        WS_VSCROLL |
        LBS_NOTIFY |
        LBS_NOINTEGRALHEIGHT,
        0,
        0,
        300,
        200,
        parent,
        nullptr,
        GetModuleHandleW(nullptr),
        nullptr);
    if (m_hwnd != nullptr)
    {
		OutputDebugStringA("ListCandidateView::Create Succeed\n");
        return true;
    }
    else
    {
        OutputDebugStringA("ListCandidateView::Create Succeed\n");
        return false;
    }
}

void ListCandidateView::SetCandidates(
    const std::vector<std::wstring>& candidates)
{
    if (m_hwnd == nullptr)
    {
        OutputDebugString(L"ListCandidateView::SetCandidates Failed m_hwnd==nullptr\n");
        return;
    }
    else
    {
        OutputDebugString(L"ListCandidateView::SetCandidates Succeed\n");
    }

    if(IsWindow(m_hwnd) == FALSE)
    {
        OutputDebugString(L"ListCandidateView::SetCandidates Failed IsWindow(m_hwnd) == FALSE\n");
        return;
    }
    else
    {
        OutputDebugString(L"ListCandidateView::SetCandidates Succeed IsWindow(m_hwnd) == TRUE\n");
	}
    SendMessageW(
        m_hwnd,
        LB_RESETCONTENT,
        0,
        0);

    int index = 1;
    for (const auto& candidate : candidates)
    {

		std::wstring wstrIndex = std::to_wstring(index) + L". ";
		std::wstring wstrCandidate = wstrIndex + candidate;
        LRESULT result = SendMessageW(
            m_hwnd,
            LB_ADDSTRING,
            0,
            reinterpret_cast<LPARAM>(wstrCandidate.c_str()));

        if (result == LB_ERR || result == LB_ERRSPACE)
        {
            OutputDebugStringW(
                L"ListCandidateView::SetCandidates: "
                L"LB_ADDSTRING failed\n");
        }
        index++;
    }
}

int ListCandidateView::GetSelectedIndex() const
{
    if (m_hwnd == nullptr)
    {
        return -1;
    }

    LRESULT result = SendMessageW(
        m_hwnd,
        LB_GETCURSEL,
        0,
        0);

    if (result == LB_ERR)
    {
        return -1;
    }

    return static_cast<int>(result);
}

void ListCandidateView::SetSelectedIndex(int index)
{
    if (m_hwnd == nullptr)
    {
        return;
    }

    SendMessageW(
        m_hwnd,
        LB_SETCURSEL,
        static_cast<WPARAM>(index),
        0);
}

void ListCandidateView::Resize(int width, int height)
{
    if (m_hwnd == nullptr)
    {
        return;
    }

    SetWindowPos(
        m_hwnd,
        nullptr,
        0,
        0,
        width,
        height,
        SWP_NOZORDER);
}