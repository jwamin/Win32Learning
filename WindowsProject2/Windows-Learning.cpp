#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "framework.h"
#include "Windows-Learning.h"
#include "Helpers.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

struct MyStruct {
    int someArbitraryMember;
};

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(pCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    MyStruct *myState = new MyStruct();

    if (myState == nullptr) {
        return 0;
    }

    myState->someArbitraryMember = 5;

    // Create the window.

    hInst = hInstance; // Store instance handle in our global variable

    HWND hwnd = CreateWindowW(szWindowClass, L"Learn to Program Windows", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, myState);

    if (!hwnd)
    {
        return FALSE;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);



    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        if (!TranslateAccelerator(hwnd, hAccelTable, &msg)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
;
    }

    return (int) msg.wParam;
}

inline MyStruct* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    MyStruct* pState = reinterpret_cast<MyStruct*>(ptr);
    return pState;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    MyStruct *myState;

    if (uMsg == WM_CREATE || uMsg == WM_NCCREATE) {
        CREATESTRUCT* mylpe = reinterpret_cast<CREATESTRUCT*>(lParam);
        myState = reinterpret_cast<MyStruct*>(mylpe->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)myState);
    }
    else {
        myState = GetAppState(hwnd);
    }

    switch (uMsg)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CLOSE:
        if (MessageBox(hwnd, L"Really Quit?", L"My Application", MB_OKCANCEL) == IDOK) {
            DestroyWindow(hwnd);
        }
        return 0;
    case WM_PAINT:
    {

        PAINTSTRUCT ps;
        LPPAINTSTRUCT pps = &ps;

        POINT point;
        RECT rect;

        HDC hdc = BeginPaint(hwnd, pps);
        // TODO: Add any drawing code that uses hdc here...
        LPRECT ptr = &ps.rcPaint;
        rect = *ptr;
        //GetClientRect(hwnd, ptr);
        //FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        point = getCenter(ptr);

        MoveToEx(hdc, 0, 0, NULL);
        LineTo(hdc, rect.right, rect.bottom);

        MoveToEx(hdc, rect.right, 0, NULL);
        LineTo(hdc, 0, rect.bottom);
        MoveToEx(hdc, point.x, point.y, NULL);
        Arc(hdc, point.x - 100, point.y - 100, point.x + 100, point.y + 100, point.x, point.y, point.x, point.y);

        EndPaint(hwnd, pps);

        INT height = rect.bottom - rect.top;
        INT width = rect.right - rect.left;
        TCHAR buffer[5000];
        swprintf(buffer, 256, L"hello width: %d, height: %d\n", width, height);
        OutputDebugString(buffer);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}