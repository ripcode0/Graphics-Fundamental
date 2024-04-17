#pragma once

#include "Common/Config.h"
#include <assert.h>
#include "Timer.h"

struct WindowState
{
    bool bPaused;
    bool bMinimized;
    bool bMaximized;
    bool bResizing;
};

typedef void (*PFNWINRESIZE)(int,int);

class Window
{
public:
    Window(int cx, int cy, const char* title);
    virtual~Window();

    
    virtual void onResize(int cx, int cy);

    void show();
    HWND getHandle() { return mHwnd;}
    virtual void swapBuffer() {};

    //PFN
    PFNWINRESIZE pfnOnResize{};

    int width;
    int height;
    HWND mHwnd;
    Timer mTimer;
    LRESULT LocalWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
private:
    WindowState mState{};
    static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};

bool executeWindow(Window* window);
//void swapChainBuffers(Window* window);

bool BeginFrame(Window* window);
void SwapFrame(Window* window);