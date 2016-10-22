#version 150 core

uniform float time;
uniform sampler2D tex;

in vec4 color;
in vec2 texCoord;

out vec4 outColor;

void main()
{
    outColor = color;
}