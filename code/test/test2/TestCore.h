#pragma once

#include <Windows.h>
#include <string>
#include <vector>

#include "CandidateWindow.h"

class TestCore
{
public:
    explicit TestCore();

    void SetCandidates(
        const std::vector<std::string>& candidates);

    void OnKeyDown(WPARAM key);

    std::string GetSelectedCandidate() const;
	int GetSelectedIndex() const { return m_selectedIndex; }
	bool IsInputFinished() const { return m_bIsInputFinished; }
    void ResetInput()
    {
        m_selectedIndex = -1;
        m_bIsInputFinished = false;
        m_candidates.clear();
        m_candidateWindow->SetCandidates(m_candidates);
	}
private:
    void MoveCandidateWindowLeft();
    void MoveCandidateWindowRight();
    void SelectCandidate(int index);
    void MoveSelection(int delta);
    void CommitCandidate();

private:
    int m_nLeftIndex = 0;
    int m_nStep = 20;
    CandidateWindow* m_candidateWindow;

    std::vector<std::string> m_candidates;
    int m_selectedIndex = -1;
	bool m_bIsInputFinished = false;
};