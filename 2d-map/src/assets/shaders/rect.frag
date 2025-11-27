#version 330 core

in vec4 chColor;
in vec2 chTex;

out vec4 outCol;
uniform sampler2D uTex;

void main()
{
    outCol = texture(uTex, chTex);
}