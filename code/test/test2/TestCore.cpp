#include "TestCore.h"

TestCore::TestCore(
    CandidateWindow& candidateWindow)
    : m_candidateWindow(candidateWindow)
{
}

void TestCore::SetCandidates(
    const std::vector<std::wstring>& candidates)
{
	m_bIsInputFinished = false;
    m_candidates = candidates;

    if (m_candidates.empty())
    {
        m_selectedIndex = -1;

        m_candidateWindow.SetCandidates(
            m_candidates);

        return;
    }

    m_selectedIndex = 0;

    m_candidateWindow.SetCandidates(
        m_candidates);

    m_candidateWindow.SetSelectedIndex(
        m_selectedIndex);
}

void TestCore::OnKeyDown(WPARAM key)
{
    if (key >= '1' && key <= '9')
    {
        const int index =
            static_cast<int>(key - '1');

        SelectCandidate(index);
        return;
    }

    switch (key)
    {
    case VK_UP:
        MoveSelection(-1);
        return;

    case VK_DOWN:
        MoveSelection(1);
        return;

    case VK_SPACE:
        CommitCandidate();
        return;
    }
}

void TestCore::SelectCandidate(int index)
{
    if (index < 0 ||
        index >= static_cast<int>(m_candidates.size()))
    {
        return;
    }

    m_selectedIndex = index;

    m_candidateWindow.SetSelectedIndex(
        m_selectedIndex);
}

void TestCore::MoveSelection(int delta)
{
    if (m_candidates.empty())
    {
        return;
    }

    int newIndex =
        m_selectedIndex + delta;

    if (newIndex < 0)
    {
        newIndex = 0;
    }

    if (newIndex >=
        static_cast<int>(m_candidates.size()))
    {
        newIndex =
            static_cast<int>(m_candidates.size()) - 1;
    }

    m_selectedIndex = newIndex;

    m_candidateWindow.SetSelectedIndex(
        m_selectedIndex);
}

void TestCore::CommitCandidate()
{
    if (m_selectedIndex < 0 ||
        m_selectedIndex >=
            static_cast<int>(m_candidates.size()))
    {
        return;
    }

	m_bIsInputFinished = true;
    const std::wstring& candidate =
        m_candidates[m_selectedIndex];

    OutputDebugStringW(
        L"Selected candidate: ");

    OutputDebugStringW(
        candidate.c_str());

    OutputDebugStringW(L"\n");

}

std::wstring TestCore::GetSelectedCandidate() const
{
    if (m_selectedIndex < 0 ||
        m_selectedIndex >=
            static_cast<int>(m_candidates.size()))
    {
        return L"";
    }
	return m_candidates[m_selectedIndex];
}