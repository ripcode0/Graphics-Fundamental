#pragma once

#include "Window.h"
#include <wglad/wglad.h>

class GLWindow : public Window
{
public:
    GLWindow(int cx, int cy, const char* title);
    virtual~GLWindow();

    void onResize(int cx, int cy) override;
    void swapBuffer() override;
    HDC mDC{};
    HGLRC mRC{};

      

};