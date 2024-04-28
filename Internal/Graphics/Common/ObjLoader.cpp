#include "ObjLoader.h"
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <windows.h>

static void load_error(const char *msg)
{
    MessageBoxA(NULL, msg, "Error", MB_OK | MB_ICONEXCLAMATION);
    exit(EXIT_FAILURE);
}

void ObjLoader::Load(const char *filename, 
    std::vector<Vertex> &verties,
    std::vector<unsigned int>& indices)
{
    //Vertex mesh{};
    char* extention = (char*)::strrchr(filename, '.') + 1;
    if(strcmp(extention, "obj") != 0){
        load_error("failed to load with obj extension");
    }

    printf("obj loading... : %s\n", filename);

    FILE* file = fopen(filename, "r");

    if(!file) return;

    char line[128];
    size_t vertex_num = 0;
    size_t st_num = 0;
    size_t normal_num = 0;
    size_t face_num = 0;
    while (!feof(file))
    {
        auto res = fscanf(file,"%s", line);
        if (res == EOF)
			break; 
        if(strcmp(line, "v") == 0){
            vertex_num++;
        }
        else if(strcmp(line, "vt") == 0){
            st_num++;
        }
        else if(strcmp(line, "vn") == 0){
            normal_num++;
        }
        else if(strcmp(line, "f") == 0){

            unsigned int v[3];
            unsigned int st[3];
            unsigned int n[3];
            int face_component = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v[0], &st[0], &n[0], 
                                                        &v[1], &st[1], &n[1], 
                                                        &v[2], &st[2], &n[2] );
            if(face_component != 9){
                load_error("unsopported face component");
            }

            face_num++;
        }
        else{
            char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
        }
    }

    printf("verties : %zd\nst : %zd\nnormals : %zd\nfaces : %zd\n",
        vertex_num, st_num, normal_num, face_num);

    ::rewind(file);

    std::vector<vec3> vertex_list(vertex_num);
    std::vector<vec2> st_list(st_num);
    std::vector<vec3> normal_list(normal_num);
    std::vector<Face> face_list(face_num);

    size_t vtx_count{};
    size_t st_count = 0;
    size_t normal_count = 0;
    size_t face_count = 0;
    while (!feof(file))
    {
        auto res = fscanf(file,"%s", line);
        
        if(strcmp(line, "v") == 0){    
            vec3* data = &vertex_list.data()[vtx_count];
            fscanf(file, "%f %f %f\n", &data->x, &data->y, &data->z);
            vtx_count++;
        }
        if(strcmp(line, "vn") == 0){
            vec3* data = &normal_list.data()[normal_count];
            fscanf(file, "%f %f %f\n", &data->x, &data->y, &data->z);
            normal_count++;
        }
        if(strcmp(line, "vt") == 0){
            vec2* data = &st_list.data()[st_count];
            fscanf(file, "%f %f\n", &data->x, &data->y);
            st_count++;
        }
        
        if(strcmp(line, "f") == 0){
            
            Face* face = &face_list.data()[face_count];
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
                    &face->v[0], &face->st[0], &face->vn[0], 
                    &face->v[1], &face->st[1], &face->vn[1], 
                    &face->v[2], &face->st[2], &face->vn[2]);
                                                        
            face_count++;
        }

    }
    
    fclose(file);

    indices.clear();
    verties.clear();
    verties.resize(vertex_num);

    for(size_t i = 0; i < face_list.size(); ++i){

        Face& face = face_list[i];

        for(size_t j = 0; j < 3; ++j){
            auto vertex_index = face.v[j] -1;
            auto st_index = face.st[j] -1;
            auto normal_index = face.vn[j] -1;

            Vertex& vtx = verties[vertex_index];
            vtx.pos = vertex_list[vertex_index];
            vtx.st = st_list[st_index];
            vtx.normal = normal_list[normal_index];

            indices.emplace_back(vertex_index);
        }
    }

    printf("indeices : %d\n", indices.size());
    int g = 0;
}

void ObjLoader::loadObj(const char *filename, std::vector<Vertex> &verties)
{
    std::ifstream file;
    file.open(filename);

    std::string line;
    std::vector<std::string> tokkens;

    std::vector<vec3> pos_list;
    std::vector<vec2> st_list;
    std::vector<vec3> normal_list;

    size_t vertex_num{};
    while (std::getline(file, line))
    {
        
        // std::stringstream ss(line);
        // std::string tokken;
        // while (std::getline(ss, tokken))
        // {
        //     //printf("%s\n", tokken.c_str());
        //     if(!tokken.compare("v")){
        //         printf("%s\n", line.c_str());
        //     }
        // }
        //const char* linestr = line.c_str();
        bool has_vertex_line = false;
        std::string linestr(line);
        char* tok = nullptr;
        tok = strtok((char*)linestr.c_str(), " ");
        while (tok != nullptr)
        {
            if(strcmp(tok, "v") == 0){
                vertex_num++;
                //printf("%s\n", line.c_str());
                has_vertex_line = true;
            }
            else{
                if(has_vertex_line){
                    printf("%f\n", std::stof(tok));
                }
            }
            tok = strtok(nullptr, " ");
        }
        
        
    }

    printf("verties num : %zd\n", vertex_num);
    while (std::getline(file, line))
    {
        tokkens = phaser::split(line, " ");

        if(!tokkens[0].compare("v")){
            vec3 pos { std::stof(tokkens[1]), std::stof(tokkens[2]), std::stof(tokkens[3])};
            pos_list.emplace_back(pos);
        }
        if(!tokkens[0].compare("vt")){
            vec2 st {std::stof(tokkens[1]), std::stof(tokkens[2])};
            st_list.emplace_back(st);
        }
        if(!tokkens[0].compare("vn")){
            vec3 normal {std::stof(tokkens[1]), std::stof(tokkens[2]), std::stof(tokkens[3])};
            normal_list.emplace_back(normal);
        }
    }

    file.close();
}

std::vector<std::string> phaser::split(std::string line, std::string delimiter)
{
    std::vector<std::string> splitLine;

    size_t pos;

    std::basic_string<char> tokken;

    while ((pos = line.find(delimiter)) != std::string::npos)
    {
        tokken = line.substr(0, pos);
        splitLine.push_back(tokken);
        line.erase(0, pos + delimiter.length());
    }
    
    splitLine.push_back(line);

    return splitLine;
}
