#pragma once

#include "Common/Config.h"
#include "wglad/wglad.h"

#define glCheckError() __glCheckError(__FILE__, __LINE__)

inline const char* _glErrorString(GLenum err){
    switch (err)
    {
    case GL_NO_ERROR:          return "No Error";
    case GL_INVALID_ENUM:      return "Invalid Enum";
    case GL_INVALID_VALUE:     return "Invalid Value";
    case GL_INVALID_OPERATION: return "Invalid Operation";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid Framebuffer Operation";
    case GL_OUT_OF_MEMORY:     return "Out of Memory";
    case GL_STACK_UNDERFLOW:   return "Stack Underflow";
    case GL_STACK_OVERFLOW:    return "Stack Overflow";
    case GL_CONTEXT_LOST:      return "Context Lost";
    default:                   return "Unknown Error";
    }
}

inline void __glCheckError(const char* file, int line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        char buf[256];
        sprintf(buf, "OpenGL Error : %s %d %u %s\n", file, line, err,_glErrorString(err));
        MessageBoxA(nullptr, "error", buf, MB_OK);
    }
    
}