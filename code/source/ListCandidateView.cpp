#include "ListCandidateView.h"
#include "CommonFunction.h"
ListCandidateView::ListCandidateView()
{
}

ListCandidateView::~ListCandidateView()
{
    if (m_hWnd != nullptr)
    {
        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }
    if (m_hFont != nullptr)
    {
        DeleteObject(m_hFont);
        m_hFont = nullptr;
    }
}

bool ListCandidateView::Create(HWND hParent, HINSTANCE hInstance)
{
    if (hParent == nullptr)
    {
        return false;
    }

    m_hWnd = CreateWindowExA(
        0,
        "LISTBOX",
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
        hParent,
        nullptr,
        GetModuleHandleW(nullptr),
        nullptr);
    if (m_hWnd != nullptr)
    {
		OutputDebugStringA("ListCandidateView::Create Succeed\n");
        //return true;
    }
    else
    {
        OutputDebugStringA("ListCandidateView::Create Failed\n");
        //return false;
    }

    m_hFont = CreateFontA(
        24,                  // 字体高度
        0,                   // 字体宽度，0 表示默认
        0,                   // 字体倾斜角度
        0,
        FW_NORMAL,           // 字重
        FALSE,               // 斜体
        FALSE,               // 下划线
        FALSE,               // 删除线
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        "Microsoft YaHei"
    );

    if (nullptr == m_hFont)
    {
        OutputDebugStringA("ListCandidateView::CreateFont Failed\n");
    }
    else
    {
        OutputDebugStringA("ListCandidateView::CreateFont Succeed\n");
    }
    SendMessageA(
        m_hWnd,
        WM_SETFONT,
        reinterpret_cast<WPARAM>(m_hFont),
        TRUE
    );

    return true;
}

void ListCandidateView::SetCandidates(
    const std::vector<std::string>& candidates)
{
    if (m_hWnd == nullptr)
    {
        OutputDebugStringA("ListCandidateView::SetCandidates Failed m_hWnd==nullptr\n");
        return;
    }
    else
    {
        OutputDebugStringA("ListCandidateView::SetCandidates Succeed\n");
    }

    if(IsWindow(m_hWnd) == FALSE)
    {
        OutputDebugStringA("ListCandidateView::SetCandidates Failed IsWindow(m_hWnd) == FALSE\n");
        return;
    }
    else
    {
        OutputDebugStringA("ListCandidateView::SetCandidates Succeed IsWindow(m_hWnd) == TRUE\n");
	}
    SendMessageA(
        m_hWnd,
        LB_RESETCONTENT,
        0,
        0);

    int index = 1;
    for (const auto& candidate : candidates)
    {

		std::string strIndex = std::to_string(index) + ". ";
		std::string strCandidate = strIndex + candidate;
		std::wstring wstrCandidate = Utf8ToUtf16(strCandidate);
        LRESULT result = SendMessageW(
            m_hWnd,
            LB_ADDSTRING,
            0,
            reinterpret_cast<LPARAM>(wstrCandidate.c_str()));

        if (result == LB_ERR || result == LB_ERRSPACE)
        {
            OutputDebugStringA(
                "ListCandidateView::SetCandidates: "
                "LB_ADDSTRING failed\n");
        }
        index++;
    }
}

int ListCandidateView::GetSelectedIndex() const
{
    if (m_hWnd == nullptr)
    {
        return -1;
    }

    LRESULT result = SendMessageA(
        m_hWnd,
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
    if (m_hWnd == nullptr)
    {
        return;
    }

    SendMessageA(
        m_hWnd,
        LB_SETCURSEL,
        static_cast<WPARAM>(index),
        0);
}

void ListCandidateView::Resize(int width, int height)
{
    if (m_hWnd == nullptr)
    {
        return;
    }

    SetWindowPos(
        m_hWnd,
        nullptr,
        0,
        0,
        width,
        height,
        SWP_NOZORDER);
}