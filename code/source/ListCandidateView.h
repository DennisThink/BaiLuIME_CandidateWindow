#pragma once

#include "ICandidateView.h"
#include "WindowBase.hpp"
class ListCandidateView : public ICandidateList,public WindowBase
{
public:
    ListCandidateView();
    ~ListCandidateView() override;

    bool Create(HWND hParent, HINSTANCE hInstance) override;

    void SetCandidates(
        const std::vector<std::wstring>& items) override;

    int GetSelectedIndex() const override;

    void SetSelectedIndex(int index) override;

    void Resize(int width, int height);
private:
    HFONT m_hFont = nullptr;
};