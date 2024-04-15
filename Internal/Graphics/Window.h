#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "Config.h"
#include <assert.h>

class Window
{
public:
    Window(int cx, int cy, const char* title);
    virtual~Window();

    void show();
    HWND getHandle() { return mHwnd;}
    virtual void swapBuffer() {};
    int widht;
    int height;
    HWND mHwnd;
    LRESULT LocalWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
private:
    static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};

bool executeWindow(Window* window);
//void swapChainBuffers(Window* window);

bool BeginFrame(Window* window);
void SwapFrame(Window* window);