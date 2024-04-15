#include "GLShader.h"
#include <filesystem>
#include <fstream>
#include <sstream>


GLDSAShader::GLDSAShader()
    : program(0)
{
    
}

GLDSAShader::GLDSAShader(LPCSTR filename, uint type)
{
    switch (type)
    {
    case GL_VERTEX_SHADER: this->type = type; break;
    case GL_FRAGMENT_SHADER: this->type = type; break;
    case GL_GEOMETRY_SHADER: this->type = type; break;
    case GL_TESS_CONTROL_SHADER: this->type = type; break;
    case GL_TESS_EVALUATION_SHADER: this->type = type; break;
    case GL_COMPUTE_SHADER: this->type = type; break;
    default:
        log_error("unable shader type");
        break;
    }
    if(!std::filesystem::exists(filename)){
        log_error("%s not found", filename);
    }
    std::ifstream is(filename, std::ios::in);
    if(!is){
        log_error("Unable to open : %s", filename);
    }
    std::stringstream code;
    code << is.rdbuf();
    is.close();
    
    this->compileFromCode(code.str().c_str(), type);
}

GLDSAShader::~GLDSAShader()
{
    glDeleteProgram(program);
}

void GLDSAShader::compileFromCode(LPCSTR code, uint type)
{
    program = glCreateShaderProgramv(type, 1, &code);

    GLint compiled = 0;
    glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glGetProgramiv(program, GL_LINK_STATUS, &compiled);

    if(compiled == GL_FALSE){
        char err[512] {};
        glGetProgramInfoLog(program, 512, nullptr, err);
        MessageBoxA(NULL, err, "Shader Compile Error : ", MB_OK);
        glDeleteProgram(program);
    }
}

void GLDSAShader::setUniform1f(const char* name, const float f){
    GLint location = glGetUniformLocation(program, name);
    glProgramUniform1f(program, location, f);
}

void GLDSAShader::setUniform2f(const char *name, const float *f)
{
    GLint location = glGetUniformLocation(program, name);
    glProgramUniform2f(program, location, f[0], f[1]);
}

void GLDSAShader::setUnifrom3f(const char* name, const float* f)
{
    GLint location = glGetUniformLocation(program, name);
    glProgramUniform3f(program, location, f[0], f[1], f[2]);
}

void GLDSAShader::setUniformMat4f(const char* name, const float* f,  bool transpose)
{
    GLint location = glGetUniformLocation(program, name);
    glProgramUniformMatrix4fv(program, location, 1, transpose, f);
}


