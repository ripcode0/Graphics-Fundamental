#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 st;
layout(location = 2) in vec3 normal;

out gl_PerVertex { vec4 gl_Position;};

layout(binding = 0) uniform UBO{
    mat4 proj;
    mat4 view;
};

out struct PS{
    vec3 normal;
}ps;

void main()
{
    gl_Position = proj * view * vec4(pos, 1);
    ps.normal = normal;
};