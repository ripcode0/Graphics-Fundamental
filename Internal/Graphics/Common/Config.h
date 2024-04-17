#pragma once

#include <iostream>
#include <stdarg.h>

// #if __has_include(<windows.h>)
// #else
// #include <windows.h>
// #endif
#include <windows.h>

#pragma warning (disable : 5082)

//type
typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef uint64_t    uint64;
typedef uint32_t    uint;

#define log_error(x, ...) __log_error(x, __FILE__, __LINE__, __VA_ARGS__)

inline void __log_error(const char* code, const char* filename, int line, ...)
{
    va_list args;
    va_start(args, code);
    char codeBuffer[256]{};

    vsnprintf_s(codeBuffer, -1, code, args);

    filename = (::strchr(filename, '\\') + 1);

    char buffer[256] {};
    sprintf_s(buffer, "file : %s\nline : %d\n\n%s\n", filename, line, codeBuffer);

    MessageBoxA(nullptr, buffer, "fatal error!", MB_OKCANCEL);
}