#include <Windows.h>

#include "TestWindow.h"

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    PWSTR,
    int)
{
    TestWindow testWindow;

    if (!testWindow.Create(hInstance))
    {
        MessageBoxW(
            nullptr,
            L"Failed to create TestWindow.",
            L"Error",
            MB_OK | MB_ICONERROR);

        return 1;
    }

    return testWindow.Run();
}