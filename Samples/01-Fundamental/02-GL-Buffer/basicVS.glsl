#version 450

out gl_PerVertex { vec4 gl_Position;};

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 st;

out struct{
    vec2 st;
}ps;

void main(){
    gl_Position = vec4(pos, 1);
    ps.st = st;
};