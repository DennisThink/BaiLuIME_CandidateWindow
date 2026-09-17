#pragma once

#include <Windows.h>
#include <memory>
#include <vector>
#include <string>
#include "ICandidateView.h"
#include "WindowBase.hpp"
#include "ListCandidateView.h"
class PreeditWindow;
class IPreeditWindow :public IPreedit, public IWindow
{
public:
    virtual ~IPreeditWindow()= default;
};

class ICandidateListWindow:public ICandidateList,public IWindow
{

};
class CandidateWindow :public IPreedit, public ICandidateList, public WindowBase
{
public:
    explicit CandidateWindow();

    ~CandidateWindow();

    virtual bool Create(HWND hParent, HINSTANCE hInstance) override;
    virtual void Destroy() override;



    void Move(int x, int y);

    //Override function for ICandidateGenerator interface
    virtual void SetUserInput(const std::wstring& strUserInput) override;
    virtual  void SetCandidates(
        const std::vector<std::wstring>& candidates) override;

    virtual int GetSelectedIndex() const override;

    virtual void SetSelectedIndex(int index) override;

protected:
    void UpdateLayout();
private:
    static LRESULT CALLBACK WndProc(
        HWND hwnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam);

    LRESULT HandleMessage(
        UINT message,
        WPARAM wParam,
        LPARAM lParam);

private:
    std::unique_ptr<PreeditWindow> m_preeditWindow;
    std::unique_ptr<ListCandidateView> m_CandidateListWindow;
};