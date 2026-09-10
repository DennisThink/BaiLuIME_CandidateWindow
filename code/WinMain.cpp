#include <windows.h>
#include "CandidateWindow.h"
#include "ListCandidateView.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    auto view = nullptr;

    CandidateWindow window(std::move(view));

    if (!window.Create(hInstance))
        return 1;

    window.Move(300, 300);
    window.Show();
    MSG msg{};

    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}