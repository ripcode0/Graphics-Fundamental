#version 450

out vec4 outFrameColor;
in struct PS{
    vec3 normal;
}ps;
void main()
{
    vec3 light_dir = normalize(-vec3(3,10, -10));

    float NdotL = dot(ps.normal, light_dir);

    outFrameColor = vec4(ps.normal,1);
}

