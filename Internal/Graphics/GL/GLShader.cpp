#include "GLShader.h"

GLDSAShader::GLDSAShader()
    : program(0)
{
    
}

GLDSAShader::GLDSAShader(LPCSTR path, uint type)
{
    if((type & GL_VERTEX_SHADER)){
        printf("vertex shader creating\n");
    }
}

GLDSAShader::~GLDSAShader()
{
    glDeleteShader(program);
}

void GLDSAShader::create(LPCSTR code, uint32 type)
{
    program = glCreateShaderProgramv(type, 1, &code);
    glObjectLabel(GL_PROGRAM, program,-1,"GLDSAShder");
    
    compile(program);
}

void GLDSAShader::setUniform1f(const char* name, float f){
    GLint location = glGetAttribLocation(program, name);
    glProgramUniform1f(program, location, f);
}

void GLDSAShader::compile(uint32 prog)
{
    GLint compiled = 0;
    glProgramParameteri(prog, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glGetProgramiv(prog, GL_LINK_STATUS, &compiled);

    if(compiled == GL_FALSE){
        char err[512] {};
        glGetProgramInfoLog(prog, 512, nullptr, err);
        MessageBoxA(NULL, err, "Shader Compile Error : ", MB_OK);
        glDeleteProgram(prog);
    }
}
