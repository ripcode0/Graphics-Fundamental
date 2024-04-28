#include "GL/GLWindow.h"
#include "Common/LinerMath.h"
#include "Common/ObjLoader.h"
#include <GL/GLShader.h>
#include <Common/LinerMath.h>

int main(int args, char* argv[])
{
    GLWindow window(1024, 780, "FPS Counter");
    wglSwapIntervalEXT(0);
    glFrontFace(GL_CCW);

    window.show();

    vec3f v1{ 2,3,1};

    std::cout << v1;

    std::vector<ObjLoader::Vertex> vertices{};
    std::vector<unsigned int> indices;
    //ObjLoader::loadObj("../../data/plane.obj", meshes);
    ObjLoader::Load("../../data/box.obj", vertices, indices);
    //ObjLoader::Load("../../data/plane.obj", vertices, indices);

    uint vbo, vao, ibo, ubo;
    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(ObjLoader::Vertex) * vertices.size(), vertices.data(), 0);

    glCreateBuffers(1, &ibo);
    glNamedBufferStorage(ibo, sizeof(unsigned int) * indices.size(), indices.data(), 0);

    glCreateVertexArrays(1, &vao);
    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, 1);
    glEnableVertexArrayAttrib(vao, 2);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(ObjLoader::Vertex, ObjLoader::Vertex::pos));
    glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(ObjLoader::Vertex, ObjLoader::Vertex::st));
    glVertexArrayAttribFormat(vao, 2, 3, GL_FLOAT, GL_FALSE, offsetof(ObjLoader::Vertex, ObjLoader::Vertex::normal));
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribBinding(vao, 1, 0);
    glVertexArrayAttribBinding(vao, 2, 0);

    vec3f a(0,1,0);
    vec3f b(0,10,1);
    auto aa = a- b;
    float adotb = vec3f::dot(a,b);


    GLShaderDSA vert_shader("modelVS.glsl", GL_VERTEX_SHADER);
    GLShaderDSA pixel_shader("modelPS.glsl", GL_FRAGMENT_SHADER);

    uint pipeline{};

    glCreateProgramPipelines(1, &pipeline);

    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vert_shader);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, pixel_shader);

    glBindProgramPipeline(pipeline);

    struct Matrices
    {
        mat4f proj;
        mat4f view;
    }matrices;
    
    int vp[4]{};
    glGetIntegerv(GL_VIEWPORT, vp);

    float aspec = (float)vp[2]/ (float)vp[3];

    matrices.proj = mat4f::perspectiveLH(45.f, aspec, 0.01, 100.f);
    matrices.view = mat4f::lookAt(vec3f(2,2,-2), vec3f(0), vec3f(0,1,0));
    
    glCreateBuffers(1, &ubo);
    glNamedBufferStorage(ubo, sizeof(Matrices), &matrices, GL_DYNAMIC_STORAGE_BIT);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

    while (BeginFrame(&window))
    {
        glClearColor(0.2,0.2,0.2,1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(ObjLoader::Vertex));

        glVertexArrayElementBuffer(vao, ibo);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        SwapFrame(&window);
    }
    
    return 0;
}