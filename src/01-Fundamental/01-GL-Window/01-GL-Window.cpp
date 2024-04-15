#include <iostream>
#include <wglad/wglad.h>

#include "GL/GLWindow.h"
#include <GL/GLShader.h>

int main(int args, char* argv[])
{
    GLWindow window(1024, 780, "GLWindow");

    LPCSTR vert = R"(
    #version 450 core

    out gl_PerVertex { vec4 gl_Position; };

    void main(){
        const vec3 vert[3] = {
            {-1, -1, 0},
            { 1, -1, 0},
            { 0,  1, 0}
        };
        gl_Position = vec4(vert[gl_VertexID],1);
    };

    )";

    LPCSTR pixel = R"(
    #version 450 core

    out vec4 outColor;
    uniform float tat;

    void main(){
        outColor= vec4(1,tat,0,1);
    }; 
    )";

    GLDSAShader test("../vertex.vs", GL_VERTEX_SHADER);

    GLDSAShader vertShader{};
    vertShader.create(vert, GL_VERTEX_SHADER);

    GLDSAShader pixelShader{};
    pixelShader.create(pixel, GL_FRAGMENT_SHADER);

    uint a = pixelShader;

    uint32 pipeline{};
    glCreateProgramPipelines(1, &pipeline);

    glBindProgramPipeline(pipeline);

    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, (GLuint)vertShader);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, (GLuint)pixelShader);

    GLuint location = glGetUniformLocation(pixelShader.program, "tata");
    glProgramUniform1f(pixelShader.program, location, 0.5f);

    pixelShader.setUniform1f("tat",0.1f);
    uint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glDeleteShader(pixelShader.program);
    window.show();

    while (BeginFrame(&window))
    {
        float color[4] = {0.2,0.1,0.1,1.f};
        glClearBufferfv(GL_COLOR, 0, color);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        SwapFrame(&window);
    }
    
    
    return 0;
}