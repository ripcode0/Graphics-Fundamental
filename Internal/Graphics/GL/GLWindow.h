#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//TODO callback func

class GLWindow
{
public:
    GLWindow(int cx, int cy, const char* title = "OpenGL");
    ~GLWindow();

    void show();
    static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
    HWND mHwnd {};
    HDC mDC {};
    HGLRC mRC {};
    bool mIsRunning = true;
};

bool ExecWindow(GLWindow* pWindow);
void SwapChain(GLWindow* pWindow);


