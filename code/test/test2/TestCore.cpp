#include "TestCore.h"

TestCore::TestCore()
{
    m_candidateWindow = new CandidateWindow();
    m_candidateWindow->Create(NULL,NULL);
}

void TestCore::MoveCandidateWindowLeft()
{
    int nNextLeft = m_nLeftIndex - m_nStep;
    if (nNextLeft > 0)
    {
        m_candidateWindow->Move(nNextLeft, nNextLeft);
        m_nLeftIndex = nNextLeft;
    }
}

void TestCore::MoveCandidateWindowRight()
{
    int nNextLeft = m_nLeftIndex + m_nStep;
    if (nNextLeft < 800)
    {
        m_candidateWindow->Move(nNextLeft, nNextLeft);
        m_nLeftIndex = nNextLeft;
    }
}


void TestCore::SetCandidates(
    const std::vector<std::string>& candidates)
{
	m_bIsInputFinished = false;
    m_candidates = candidates;

    if (m_candidates.empty())
    {
        m_selectedIndex = -1;

        m_candidateWindow->SetUserInput("nihao");
        m_candidateWindow->SetCandidates(
            m_candidates);
        m_candidateWindow->Show();

        return;
    }

    m_selectedIndex = 0;

    std::string strUserInput = std::to_string(std::rand());
    m_candidateWindow->SetUserInput(strUserInput);
    m_candidateWindow->SetCandidates(
        m_candidates);

    m_candidateWindow->SetSelectedIndex(
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
    case VK_LEFT:
        {
            MoveCandidateWindowLeft();
        }break;
    case VK_RIGHT:
    {
        MoveCandidateWindowRight();
    }break;
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

    m_candidateWindow->SetSelectedIndex(
        m_selectedIndex);
    m_candidateWindow->Show();
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

    m_candidateWindow->SetSelectedIndex(
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
    const std::string& candidate =
        m_candidates[m_selectedIndex];

    OutputDebugStringW(
        L"Selected candidate: ");

    OutputDebugStringA(
        candidate.c_str());

    OutputDebugStringW(L"\n");

}

std::string TestCore::GetSelectedCandidate() const
{
    if (m_selectedIndex < 0 ||
        m_selectedIndex >=
            static_cast<int>(m_candidates.size()))
    {
        return "";
    }
	return m_candidates[m_selectedIndex];
}