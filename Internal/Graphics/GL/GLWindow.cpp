#pragma once

#include <GL/GLConfig.h>
#include "GLWindow.h"

GLWindow::GLWindow(int cx, int cy, const char *title) 
    : Window(cx, cy, title) 
{
    HRESULT res = WGL::createGLContextFromHwnd(mHwnd, &mRC, &mDC);
    if(FAILED(res)) log_error("failed to create opengl context");
    RECT rc{};
    ::GetClientRect(mHwnd, &rc);
    width = rc.right - rc.left;
    height = rc.bottom - rc.top;
}
GLWindow::~GLWindow()
{
    WGL::releaseGLContext(mHwnd, mRC, mDC);
}

void GLWindow::onResize(int cx, int cy)
{
    if(mRC && mDC){
        printf("viewport %d : %d\n", cx, cy);
        glViewport(0, 0, cx, cy);
    }
    if(pfnOnResize) pfnOnResize(cx, cy);
}

void GLWindow::swapBuffer()
{
    if(mDC) ::SwapBuffers(mDC);
}
