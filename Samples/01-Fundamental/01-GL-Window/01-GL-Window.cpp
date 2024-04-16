#include <iostream>
#include <wglad/wglad.h>

#include "GL/GLWindow.h"
#include <GL/GLShader.h>

#include <math.h>

int main(int args, char* argv[])
{
    GLWindow window(1024, 780, "GLWindow");

    LPCSTR vert = R"(
    #version 450 core

    out gl_PerVertex { 
        vec4 gl_Position;
        float gl_PointSize;
    };

    uniform mat4 rotation;

    void main(){
        const vec3 vert[3] = {
            {-0.5, -0.5, 0},
            { 0.5, -0.5, 0},
            {   0,  0.5, 0}
        };
        gl_Position = rotation * vec4(vert[gl_VertexID],1);
    };

    )";

    LPCSTR pixel = R"(
    #version 450 core

    out vec4 outColor;
    uniform vec3 color;

    void main(){
        outColor= vec4(color,1);
    }; 
    )";

    

    GLShaderDSA vertShader{};
    vertShader.compileFromCode(vert, GL_VERTEX_SHADER);

    GLShaderDSA pixelShader{};
    pixelShader.compileFromCode(pixel, GL_FRAGMENT_SHADER);

    uint32 pipeline{};
    glCreateProgramPipelines(1, &pipeline);

    glBindProgramPipeline(pipeline);

    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, (GLuint)vertShader);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, (GLuint)pixelShader);

    //PI 180 digree
    float PI = std::acosf(-1);
    printf("MPI %f\n" ,PI);

    float a = std::cosf(90.f * (PI/180.f));
    printf("%f rot", a);

    float rotation[] = {
            1, 0,0,0,
            0, -1,0,0,
            0, 0,1,0,
            0, 0,0,1
        };

    vertShader.setUniformMat4f("rotation", rotation, true);

    uint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //glDeleteShader(pixelShader.program);
    window.show();
    glPointSize(15);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);

    while (BeginFrame(&window))
    {
        float color[4] = {0.2,0.1,0.1,1.f};
        glClearBufferfv(GL_COLOR, 0, color);

        float VertexColor[3] = {0.7,0.7,0.3};
        pixelShader.setUnifrom3f("color", VertexColor);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        float pointColor[] = {0.9,0.8,0.8};
        pixelShader.setUnifrom3f("color", pointColor);
        glDrawArrays(GL_POINTS, 0, 3);

        SwapFrame(&window);
    }
    
    
    return 0;
}