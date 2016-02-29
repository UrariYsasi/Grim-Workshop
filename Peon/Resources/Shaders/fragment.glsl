#version 150 core

uniform float time;
uniform sampler2D texKitten;

in vec3 color;
in vec2 texCoord;

out vec4 outColor;

void main()
{
    outColor = vec4(color, 1.0) * texture(texKitten, texCoord);
}