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

struct GLShaderDSA : public NonCopyable
{
    GLShaderDSA();
    GLShaderDSA(LPCSTR path, uint type);
    ~GLShaderDSA();

    void compileFromCode(LPCSTR code, uint type);

    operator GLuint() { return program;}

    uint program{};
    uint type;

    void setUniform1f(const char* name, const float f);
    void setUniform2f(const char* name, const float* f);
    void setUnifrom3f(const char *name, const float* f);
    void setUniformMat4f(const char* name, const float* f, bool transpose = false);

};
