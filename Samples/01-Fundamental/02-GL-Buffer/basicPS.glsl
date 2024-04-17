#version 450

out vec4 outColor;

in struct{
    vec2 st;
}ps;

layout(std140, binding = 0) uniform UBO{
    vec2 res;
}ubo;

layout(std140, binding = 1) uniform Delta{
    float delta;
}ubo1;

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

    //float dist = length(uv) * 2 * checker(uv, 18);
    float dist = length(uv) * 3;

    vec3 A = vec3(cos(ubo1.delta),sin(ubo1.delta), cos(ubo1.delta));
    //vec3 A = vec3(cos(ubo1.delta),1,0);
    vec3 B = vec3(0);

    float mincos = min(max(cos(ubo1.delta), 0.3), 0.9);
    float minsin = min(max(sin(ubo1.delta), 0.2), 0.8);
    vec3 color = mix(A, B, smoothstep(mincos, minsin ,dist));

    outColor = vec4(color,1);
   
};

