#pragma once

#include <GL/GLConfig.h>
#include "GLWindow.h"

GLWindow::GLWindow(int cx, int cy, const char *title)
{
    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
    wc.lpszClassName = "ModernOpenGL";
    wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
    wc.lpfnWndProc = GLWindow::WndProc;

    ATOM res = RegisterClassExA(&wc);

    int x = (GetSystemMetrics(SM_CXSCREEN) - cx) /2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - cy) /2;

    DWORD style = WS_OVERLAPPEDWINDOW;
    mHwnd = CreateWindowExA(NULL, wc.lpszClassName, title,
     style, x, y, cx, cy, nullptr, 0, wc.hInstance, 0
     );

    if(!mHwnd) log_error("failed to create window");

    ShowWindow(mHwnd, TRUE);

}
GLWindow::~GLWindow()
{
    UnregisterClassA("ModernOpenGL", GetModuleHandleA(nullptr));
    DestroyWindow(mHwnd);
}

LRESULT GLWindow::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_SIZE:{
        if(wp == WM_ENTERSIZEMOVE){
            printf("called WM_ENTERSIZEZONE\n");
        }
        if(wp == WM_EXITSIZEMOVE){
            printf("called WM_ENTERSIZEZONE\n");
        }
        //printf("WM_SIZE %d\n", (int)wp);
    }break;
    case WM_WINDOWPOSCHANGED:{
        printf("WM_CHANGED %d\n", (int)wp);
    }break;
    case WM_CLOSE:{
        SendMessageA(hwnd, WM_QUIT, 0,0);
    }break;
    
    default:
        break;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}
