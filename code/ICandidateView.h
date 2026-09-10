#pragma once

#include <Windows.h>
#include <string>
#include <vector>

class ICandidateView
{
public:
    virtual ~ICandidateView() = default;

    virtual bool Create(HWND parent) = 0;

    virtual void SetCandidates(
        const std::vector<std::wstring>& items) = 0;

    virtual int GetSelectedIndex() const = 0;

    virtual void SetSelectedIndex(int index) = 0;

    virtual void Resize(int width, int height) = 0;
};