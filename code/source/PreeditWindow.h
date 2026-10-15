#pragma once

#include <Windows.h>
#include <string>

class PreeditWindow
{
public:
    PreeditWindow() = default;
    ~PreeditWindow();

    PreeditWindow(const PreeditWindow&) = delete;
    PreeditWindow& operator=(const PreeditWindow&) = delete;

public:
    bool Create(HWND hParent, HINSTANCE hInstance);
    void Destroy();

    void Show();
    void Hide();

    void SetText(const std::string& text);

    // 创建并设置字体
    bool CreateFont(
        int height,
        int weight,
        const wchar_t* fontName
    );

    void SetWindowTextColor(COLORREF color);
    void SetBackgroundColor(COLORREF color);

    void SetBounds(
        int x,
        int y,
        int width,
        int height
    );

    HWND GetHandle() const;

private:
    static constexpr wchar_t CLASS_NAME[] =
        L"WhiteDeer_PreeditWindow";

    static bool RegisterWindowClass(HINSTANCE hInstance);

    static LRESULT CALLBACK WndProc(
        HWND hwnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

    LRESULT HandleMessage(
        HWND hwnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

    void OnPaint();

private:

    HWND m_hWnd;
    HINSTANCE m_hInstance;
    std::string m_text;

    HFONT m_hFont = nullptr;

    COLORREF m_textColor = RGB(0, 0, 0);
    COLORREF m_backgroundColor = RGB(255, 255, 255);
};