#include "GLShader.h"
#include <filesystem>
#include <fstream>
#include <sstream>




GLShaderDSA::GLShaderDSA()
    : program(0)
{
    
}

GLShaderDSA::GLShaderDSA(std::string filename, uint type)
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

GLShaderDSA::~GLShaderDSA()
{
    glDeleteProgram(program);
}

void GLShaderDSA::compileFromCode(LPCSTR code, uint type)
{
    program = glCreateShaderProgramv(type, 1, &code);

    GLint compiled = 0;
    //glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);//i dont think it's nessesary
    glGetProgramiv(program, GL_LINK_STATUS, &compiled);

    if(compiled == GL_FALSE){
        char err[512] {};
        glGetProgramInfoLog(program, 512, nullptr, err);
        MessageBoxA(NULL, err, "Shader Compile Error : ", MB_OK);
        glDeleteProgram(program);
    }
}

void GLShaderDSA::setUniform1f(const char* name, const float f){
    GLint location = glGetUniformLocation(program, name);
    glProgramUniform1f(program, location, f);
}

void GLShaderDSA::setUniform2f(const char *name, const float *f)
{
    GLint location = glGetUniformLocation(program, name);
    glProgramUniform2f(program, location, f[0], f[1]);
}

void GLShaderDSA::setUnifrom3f(const char* name, const float* f)
{
    GLint location = glGetUniformLocation(program, name);
    glProgramUniform3f(program, location, f[0], f[1], f[2]);
}

void GLShaderDSA::setUniformMat4f(const char* name, const float* f,  bool transpose)
{
    GLint location = glGetUniformLocation(program, name);
    glProgramUniformMatrix4fv(program, location, 1, transpose, f);
}


