#pragma once

#include "GLConfig.h"

//GLShader uused DSA 

struct NonCopyable
{
    //NonCopyable() = delete;
    NonCopyable() = default;
    NonCopyable(const NonCopyable& rhs) = delete;
    NonCopyable& operator=(const NonCopyable& rhs) = delete;
    //operator GLShader() = delete;
};

struct GLDSAShader : public NonCopyable
{
    GLDSAShader();
    GLDSAShader(LPCSTR path, uint type);
    ~GLDSAShader();

    void create(LPCSTR code, uint32 type);
    //explicit operator GLuint() { return shader;}
    operator GLuint() { return program;}

    uint program{};
    uint type;
    void setUniform1f(const char* name, float f);
private:
    void compile(uint32 prog);
};

struct GLRawShader
{
    GLRawShader(){};

    

    uint32 program;
};
