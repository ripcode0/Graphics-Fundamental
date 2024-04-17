#version 450

out vec4 outColor;

in struct{
    vec2 st;
}ps;

layout(std140, binding = 0) uniform UBO{
    vec2 res;
}ubo;

float checker(vec2 uv, float repeat){
    float cx = floor(repeat * uv.x);
    float cy = floor(repeat * uv.y);
    float res = mod(cx * cy, 2.0);
    return sign(res);
}
#define TWO_PI 6.28318530718
void main()
{   
    vec2 res = ubo.res;
    vec2 st = ps.st;
    float ratio = res.x / res.y;
    vec2 uv = st;
    uv -= 0.5;

    float dist = length(uv);

    vec3 A = vec3(1,1,0);
    vec3 B = vec3(0);

    vec3 color = mix(A, B, smoothstep(0.3, 0.305,dist));

    outColor = vec4(color,1);
   
};

