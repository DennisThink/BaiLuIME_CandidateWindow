#pragma once

#include <Windows.h>
#include <string>
#include <vector>

#include "CandidateWindow.h"
#include "TestCore.h"

class TestWindow
{
public:
    TestWindow();
    ~TestWindow();

    bool Create(HINSTANCE hInstance);
    int Run();

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

    void OnCreate();
    void OnKeyDown(WPARAM key);
    void OnPaint();
    void OnSize(int width, int height);
    void OnDestroy();

    void SwitchCandidateSet();
    void UpdateStatus();
    void ResetInput();

private:
    HWND m_hwnd = nullptr;
    HINSTANCE m_hInstance = nullptr;

    CandidateWindow m_candidateWindow;
    TestCore m_core;

    std::vector<std::vector<std::wstring>>
        m_candidateSets;

    int m_candidateSetIndex = 0;

    std::wstring m_lastCommitted;
};