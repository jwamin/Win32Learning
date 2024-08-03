#include "framework.h"
#include "Helpers.h"

void draw(HWND hWnd) {
    PAINTSTRUCT ps;
    LPPAINTSTRUCT pps = &ps;
    const COLORREF rgbRed = 0x000000FF;
    const COLORREF yellow = RGB(242, 252, 150);
    TCHAR buffer[5000];
    POINT point;
    RECT rect;
    SIZE size;
    HDC hdc = BeginPaint(hWnd, pps);
    // TODO: Add any drawing code that uses hdc here...
    LPRECT ptr = &rect;
    LPSIZE sizePtr = &size;
    HBRUSH brush = CreateSolidBrush(rgbRed);
    HBRUSH yellowBrush = CreateSolidBrush(yellow);

    GetClientRect(hWnd, ptr);

    size.cx = rect.bottom - rect.top;
    size.cy = rect.right - rect.left;
    BOOL isSquare = size.cx == size.cy;

    if (isSquare) {
        MoveToEx(hdc, 0, 0, NULL);
        FillRect(hdc, ptr, brush);
    }

    point = getCenter(ptr);

    if (!isSquare) {
        Arc(hdc, point.x - 100, point.y - 100, point.x + 100, point.y + 100, point.x, point.y, point.x, point.y);
    }
    else {
        SelectObject(hdc, yellowBrush);
        Ellipse(hdc, point.x - 100, point.y - 100, point.x + 100, point.y + 100);
    }

    MoveToEx(hdc, 0, 0, NULL);
    LineTo(hdc, rect.right, rect.bottom);
    MoveToEx(hdc, rect.right, 0, NULL);
    LineTo(hdc, 0, rect.bottom);
    MoveToEx(hdc, point.x, point.y, NULL);

    EndPaint(hWnd, pps);

    swprintf(buffer, 256, L"hello width: %d, height: %d\n", size.cx, size.cy);
    if (isSquare) {
        swprintf(buffer, 256, L"it's square!\n");
    }
    OutputDebugString(buffer);
}