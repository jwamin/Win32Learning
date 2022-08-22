#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "framework.h"
#include "Windows-Learning.h"
#include "Helpers.h"
#include "MyProgramClass.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

    // Create the window.
    MyProgramClass myClass;
    
    myClass.Create(L"Learn To Program windows", WS_OVERLAPPEDWINDOW);

    ShowWindow(myClass.Window(), nCmdShow);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    HWND win = myClass.Window();
    MSG msg;
    
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        if (!TranslateAccelerator(win, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
;
    }

    return (int) msg.wParam;
}

