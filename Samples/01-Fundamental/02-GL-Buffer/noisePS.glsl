#version 450

out vec4 outColor;

in struct PS{
    vec2 st;
}ps;

layout(std140, binding = 0) uniform UBO{
    vec2 res;
}ubo;

layout(std140, binding = 1) uniform Delta{
    float delta;
}ubo1;


mat2 rotate2D(float r) {
    return mat2(cos(r), sin(r), -sin(r), cos(r));
}


void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    float scale = 1000;
    vec2 res = ubo.res;
    vec2 uv = (vec2((ps.st -.5 * res.xy)) / res.y) * scale;
    vec3 col = vec3(0);
    float t = ubo1.delta;
    
    vec2 n = vec2(0),q;
    vec2 N = vec2(0);
    vec2 p = uv + sin(t*0.1)/10.;
    float S = 10.;
    mat2 m = rotate2D(1);
    //mat2 m = mat2(0,1,1,1);

    // for(float j=0.;j <300.f; j+=1){
    //   p*=m;
    //   n*=m;
    //   q=p*S+j+n+t;
    //   n+=sin(q);
    //   N+=cos(q)/S;
    //   S*=1.2;
      
    // }
    
    //col = vec3(1, 2, 4) * pow((N.x + N.y + 0.2)+.005/length(N), 2.1);
    
    col=pow(max(vec3(0),(N.x+N.y+.5)*.1*vec3(8,1,2)+.003/length(N)),vec3(.9));
    
    
    // Output to screen
    outColor = vec4(col,1.0);
}