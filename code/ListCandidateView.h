#pragma once

#include "ICandidateView.h"

class ListCandidateView : public ICandidateView
{
public:
    ListCandidateView();
    ~ListCandidateView() override;

    bool Create(HWND parent) override;

    void SetItems(
        const std::vector<std::wstring>& items) override;

    int GetSelectedIndex() const override;

    void SetSelectedIndex(int index) override;

    void Resize(int width, int height) override;

private:
    HWND m_hwnd = nullptr;
};