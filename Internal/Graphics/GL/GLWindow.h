#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//TODO callback func

class GLWindow
{
public:
    GLWindow(int cx, int cy, const char* title);
    ~GLWindow();


    static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
    HWND mHwnd;
};