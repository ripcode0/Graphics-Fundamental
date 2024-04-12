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
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = GLWindow::WndProc;

    ATOM res = RegisterClassExA(&wc);

    int x = (GetSystemMetrics(SM_CXSCREEN) - cx) /2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - cy) /2;

    DWORD style = WS_OVERLAPPEDWINDOW;
    mHwnd = CreateWindowExA(NULL, wc.lpszClassName, title,
     style, x, y, cx, cy, nullptr, 0, wc.hInstance, 0
     );

    if(!mHwnd) log_error("failed to create window");

    WGL::createGLContextFromHwnd(mHwnd, &mRC, &mDC);
}

GLWindow::~GLWindow()
{
    WGL::releaseGLContext(mHwnd, mRC, mDC);
    UnregisterClassA("ModernOpenGL", GetModuleHandleA(nullptr));
    DestroyWindow(mHwnd);
}

void GLWindow::show()
{
    int command = SW_SHOWNA; //show window but not active

    STARTUPINFOA si = {sizeof(si)};
    GetStartupInfoA(&si);

    if(si.dwFlags & STARTF_USESHOWWINDOW){
        command = si.wShowWindow;
    }
    ::ShowWindow(mHwnd, command);
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
        printf("close");
        PostQuitMessage(0);
    }break;
    
    default:
        break;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

bool ExecWindow(GLWindow *pWindow)
{
    if(!pWindow) return false;

    MSG msg{};
    if(PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)){
        if(msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE){
            PostQuitMessage(0);
            pWindow->mIsRunning = false;
        }
        if(msg.message == WM_QUIT) 
            pWindow->mIsRunning = false;

        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    } 
    return pWindow->mIsRunning;
}

void SwapChain(GLWindow *pWindow)
{
    if(!pWindow->mDC) log_error("HDC dosent created");
    SwapBuffers(pWindow->mDC);
}
