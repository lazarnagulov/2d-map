#version 330 core

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTex;

out vec4 chColor;
out vec2 chTex;

void main()
{
    gl_Position = vec4(inPos.xy, 0.0, 1.0);
    chColor = vec4(inColor, 1.0);
    chTex = inTex;
}