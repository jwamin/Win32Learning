#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "framework.h"
#include "Windows-Learning.h"
#include "Helpers.h"
#include "MyProgramClass.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name





int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

    // Create the window.
    MyProgramClass myClass;
    
    if (!myClass.Create(L"Learn To Program windows",WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(myClass.Window(), nCmdShow);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        if (!TranslateAccelerator(myClass.Window(), hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
;
    }

    return (int) msg.wParam;
}

