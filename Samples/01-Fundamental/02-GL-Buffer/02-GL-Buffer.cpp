#include <GL/GLWindow.h>
#include <GL/GLShader.h>

int main(int args, char* argv[])
{
    GLWindow window(1024, 780, "Modern OpenGL 4.6 Buffers");

    //Left Hand System
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    //            ST                      POS(INDEX)
    // [0,1] ------------ [1,1]  [-1, 1] 1 --------- [1, 1] 2          
    //   |					|       |				   |
    //   |					|       |				   |
    //   |					|       |			       |
    //   |					|       |				   |
    //   |					|       |		  	       |
    //   |		  			|       |				   |
    // [0,0] ------------ [1,0]  [-1,-1] 0 --------- [1,-1] 3

    float point = 0.5f;

    float quad[4][5] = {
        {-point, -point, 0.f, 0.0f, 0.0f},
        {-point,  point, 0.f, 0.0f, 1.0f},
        { point,  point, 0.f, 1.0f, 1.0f},
        { point, -point, 0.f, 1.0f, 0.0f},
    };

    uint indices[] = { 0, 1, 2, 0, 2, 3};

    uint vbo, vao, ibo;

    //Create VBO
    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(quad), quad, 0);

    //Create IBO
    
    glCreateBuffers(1, &ibo);
    glNamedBufferStorage(ibo, sizeof(indices), indices, 0);
    
    //Create VAO
    glCreateVertexArrays(1, &vao);
    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, 1);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribBinding(vao, 1, 0);
    //Bind Vao to Context
    glBindVertexArray(vao);

    //create UBO
    uint ubo;
    glCreateBuffers(1, &ubo);
    glNamedBufferStorage(ubo, sizeof(float) * 2, nullptr, GL_DYNAMIC_STORAGE_BIT);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

    GLShaderDSA vertShader("basicVS.glsl", GL_VERTEX_SHADER);
    GLShaderDSA pixelShader("basicPS.glsl", GL_FRAGMENT_SHADER);

    uint pipeline{};
    glCreateProgramPipelines(1, &pipeline);

    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vertShader);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, pixelShader);

    window.show();
    while (BeginFrame(&window))
    {
        float clearColor[] = { 0.2, 0.2, 0.2, 1.f};
        float depth = 1.f;
        glClearBufferfv(GL_COLOR, 0, clearColor);
        glClearBufferfv(GL_DEPTH, 0, &depth);

        //get current main vao from context
        GLint currentVAO{};
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);

        //bind ibo vbo to vao
        glVertexArrayElementBuffer(currentVAO, ibo);
        glVertexArrayVertexBuffer(currentVAO, 0, vbo, 0, sizeof(3) * 5);

        //get width,height and update ubo
        GLint viewport[4] ={};
        glGetIntegerv(GL_VIEWPORT, viewport);

        float resolution[2] = {(float)viewport[2], (float)viewport[3]};
        glNamedBufferSubData(ubo, 0, sizeof(float) * 2, resolution);

        //bind shader stage pipeline
        glBindProgramPipeline(pipeline);
        
        //draw
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        SwapFrame(&window);
    }
    
    return 0;
}