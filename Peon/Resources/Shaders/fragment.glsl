#version 150 core

uniform float time;
uniform sampler2D texKitten;

in vec4 color;
in vec2 texCoord;

out vec4 outColor;

void main()
{
    outColor = color * texture(texKitten, texCoord);
}