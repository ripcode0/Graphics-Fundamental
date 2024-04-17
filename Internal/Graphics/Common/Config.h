#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
//#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
//#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
//#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#include <windows.h>
#include <iostream>
#include <stdarg.h>

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