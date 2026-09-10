#pragma once

#include <Windows.h>
#include <memory>
#include <vector>
#include <string>
class ICandidateView;

class CandidateWindow
{
public:
    explicit CandidateWindow(
        std::unique_ptr<ICandidateView> view);

    ~CandidateWindow();

    bool Create(HINSTANCE hInstance);


    void Show();
    void Hide();

    void Move(int x, int y);

    void SetCandidates(
        const std::vector<std::wstring>& candidates);

    int GetSelectedIndex() const;

    void SetSelectedIndex(int index);

    HWND GetHandle() const;
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
    HWND m_hwnd = nullptr;
    HINSTANCE m_hInstance = nullptr;

    std::unique_ptr<ICandidateView> m_view;
};