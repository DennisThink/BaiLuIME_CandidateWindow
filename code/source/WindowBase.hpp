#pragma once

#include <Windows.h>

class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual bool Create(HWND hParent, HINSTANCE hInstance) = 0;
    virtual void Destroy()=0;

    virtual void Show()=0;
    virtual void Hide()=0;

    virtual void SetPosition(int x, int y)=0;
    virtual void SetSize(int width, int height)=0;
    virtual void SetBounds(int x, int y, int width, int height)=0;
    virtual HWND GetHandle() const=0;
};
class WindowBase:public IWindow
{
public:
    virtual ~WindowBase() = default;

    virtual bool Create(HWND hParent, HINSTANCE hInstance) = 0;
    virtual void Destroy() override;

    virtual void Show() override;
    virtual void Hide() override;

    virtual void SetPosition(int x, int y) override;
    virtual void SetSize(int width, int height) override;
    virtual void SetBounds(int x, int y, int width, int height) override;

    virtual HWND GetHandle() const override;

protected:
    HWND m_hWnd = nullptr;
    HINSTANCE m_hInstance = nullptr;
};