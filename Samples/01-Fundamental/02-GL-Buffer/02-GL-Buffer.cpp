#include <GL/GLWindow.h>
#include <GL/GLShader.h>

int main(int args, char* argv[])
{
    GLWindow window(1024, 780, "Modern OpenGL 4.6 Buffers");

    //Left Hand System
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_DEPTH_STENCIL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // 1 -------2
    // |
    // |
    // 0

    float point = 0.5f;

    float tri[3][3] = {
        {-point, -point, 0.f},
        {-point,  point, 0.f},
        { point,  point, 0.f}
    };

    float quad[4][3] = {
        {-point, -point, 0.f},
        {-point,  point, 0.f},
        { point,  point, 0.f},
        { point, -point, 0.f},
    };    

    uint triVBO, quadVBO, vao, ibo;

    glCreateBuffers(1, &triVBO);
    glNamedBufferStorage(triVBO, sizeof(tri), tri, GL_DYNAMIC_STORAGE_BIT);

    {
        glCreateBuffers(1, &quadVBO);
        glNamedBufferStorage(quadVBO, sizeof(quad), quad, GL_DYNAMIC_STORAGE_BIT);

        uint indices[] = { 0,1,2,0,2,3};
        glCreateBuffers(1, &ibo);
        glNamedBufferData(ibo, sizeof(indices), indices, GL_STATIC_DRAW);
    }
    

    glCreateVertexArrays(1, &vao);
    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);

    GLShaderDSA vertShader("basic.vs", GL_VERTEX_SHADER);
    GLShaderDSA pixelShader("basic.fs", GL_FRAGMENT_SHADER);

    uint pipeline{};
    glCreateProgramPipelines(1, &pipeline);

    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vertShader);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, pixelShader);

    glBindProgramPipeline(pipeline);


    window.show();
    while (BeginFrame(&window))
    {
        float clearColor[] = { 0.2, 0.2, 0.2, 1.f};
        float depth = 1.f;
        glClearBufferfv(GL_COLOR, 0, clearColor);
        glClearBufferfv(GL_DEPTH, 0, &depth);

        glBindVertexArray(vao);
        glVertexArrayVertexBuffer(vao, 0, triVBO, 0, sizeof(float) * 3);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        //get current vao binding
        // GLint currentVAO{};
        // glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);

        // glVertexArrayElementBuffer(currentVAO, ibo);

        // glVertexArrayVertexBuffer(currentVAO, 0, quadVBO, 0, sizeof(3) * 3);

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        SwapFrame(&window);
    }
    
    return 0;
}