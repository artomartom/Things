

#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#define H_FAIL(hr) (hr != S_OK)

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#define RECTWIDTH(x) (x.right - x.left)
#define RECTHEIGHT(x) (x.bottom - x.top)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HelloWndProc(HWND, UINT, WPARAM, LPARAM);

 

int main()
{
    static WCHAR mainWnd[]{L"HelloApplication"};
    static WCHAR childWnd[]{L"SineApplication"};
    HWND mainHandle, childHandle;
    MSG msg;
    WNDCLASSEXW wndclass{};
    wndclass.cbSize = sizeof(WNDCLASSEXW);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = HelloWndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = sizeof(long);
    wndclass.hInstance = GetModuleHandle(0);
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = mainWnd;

    if (!RegisterClassExW(&wndclass))
    {
        return 0;
    }
    wndclass.lpszClassName = childWnd;

    if (!RegisterClassExW(&wndclass))
    {
        return 0;
    }

    mainHandle = CreateWindowExW(0, mainWnd,
                                 L"Hello World for Windows",
                                 WS_OVERLAPPEDWINDOW,
                                 CW_USEDEFAULT,
                                 CW_USEDEFAULT,
                                 CW_USEDEFAULT,
                                 CW_USEDEFAULT,
                                 NULL,
                                 NULL,
                                 GetModuleHandle(0),
                                 NULL);

    childHandle = CreateWindowExW(0, childWnd,
                                  L"Hello World",
                                  WS_CHILD | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  300,
                                  300,
                                  mainHandle,
                                  NULL,
                                  GetModuleHandle(0),
                                  NULL);

    ShowWindow(mainHandle, SW_SHOWDEFAULT);
    UpdateWindow(mainHandle);
    ShowWindow(childHandle, SW_SHOWDEFAULT);
    UpdateWindow(childHandle);

    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    float RTVClearColor[]{0.2f, 0.2f, 0.2f, 1.f};
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch (message)
    {

    case WM_PAINT:
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, message, wParam, lParam);
}