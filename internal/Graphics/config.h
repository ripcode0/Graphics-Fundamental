#pragma once

#include <iostream>
#include <stdarg.h>

#if __has_include(<windows.h>)
#else
#include <windows.h>
#endif

#pragma warning(disble : 5082)

//type
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;

inline void _log_error(const char* code, const char* filename, int line)
{
    va_list args;
    va_start(args, code);
    char codeBuffer[256]{};

    vsnprintf_s(codeBuffer, -1, code, args);

    filename = (::strchr(filename, '\\') + 1);

    char buffer[256] {};
    sprintf_s(buffer, "file : %s\nline : %d\n\n%s\n", filename, line, codeBuffer);

    
}