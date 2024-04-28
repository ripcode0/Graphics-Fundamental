#pragma once

#include <vector>
#include <string>

namespace ObjLoader
{
    struct vec3{
        //vec3(){}
        //vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
        float x, y, z;
    };
    struct vec2{
        float x, y;
    };
    
    struct Vertex
    {
        vec3 pos;
        vec2 st;
        vec3 normal;
    };
    
    struct FaceIndex
    {
        unsigned int index[3];
    };
    

    struct Face
    {
        uint32_t v[3];
        uint32_t st[3];
        uint32_t vn[3];        
    };
    
    
    void Load(_In_ const char* filename, 
        _Out_ std::vector<Vertex>& vertices, 
        _Out_ std::vector<unsigned int>& indices);
        
    void loadObj(const char* filename, std::vector<Vertex>& verties);
};

namespace phaser
{
    std::vector<std::string> split(std::string line, std::string delimiter);
};