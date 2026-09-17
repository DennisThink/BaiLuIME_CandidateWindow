#pragma once

#include <Windows.h>
#include <string>
#include <vector>

//Preedit=Pre-edit
class IPreedit
{
public:
    virtual ~IPreedit()=default;
    virtual void SetUserInput(const std::wstring& strUserInput) = 0;
};

class ICandidateList
{
public:
    virtual ~ICandidateList() = default;
    virtual void SetCandidates(
        const std::vector<std::wstring>& items) = 0;
    virtual int GetSelectedIndex() const = 0;
    virtual void SetSelectedIndex(int index) = 0;
};