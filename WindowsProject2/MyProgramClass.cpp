#include "MyProgramClass.h"
#include "Helpers.h"

    LRESULT MyProgramClass::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg)
        {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                //DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, &About);
                break;
            case IDM_EXIT:
                DestroyWindow(m_hwnd);
                break;
            default:
                return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
            }
        }
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_CLOSE:
            if (MessageBox(m_hwnd, L"Really Quit?", L"My Application", MB_OKCANCEL) == IDOK) {
                DestroyWindow(m_hwnd);
            }
            return 0;
        case WM_PAINT:
        {

            PAINTSTRUCT ps;
            LPPAINTSTRUCT pps = &ps;

            POINT point;
            RECT rect;

            HDC hdc = BeginPaint(m_hwnd, pps);
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

            EndPaint(m_hwnd, pps);

            INT height = rect.bottom - rect.top;
            INT width = rect.right - rect.left;
            TCHAR buffer[5000];
            swprintf(buffer, 256, L"hello width: %d, height: %d\n", width, height);
            OutputDebugString(buffer);
        }
        return 0;

        }
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }

    // Message handler for about box.
    INT_PTR CALLBACK MyProgramClass::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
    };
