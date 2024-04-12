#pragma once

#include <GL/GLConfig.h>
#include "GLWindow.h"

GLWindow::GLWindow(int cx, int cy, const char *title) 
    : Window(cx, cy, title) 
{
    HRESULT res = WGL::createGLContextFromHwnd(mHwnd, &mRC, &mDC);
    if(FAILED(res)) log_error("failed to create opengl context");
}
GLWindow::~GLWindow()
{
    WGL::releaseGLContext(mHwnd, mRC, mDC);
}

void GLWindow::swapBuffer()
{
    if(mDC) ::SwapBuffers(mDC);
}
