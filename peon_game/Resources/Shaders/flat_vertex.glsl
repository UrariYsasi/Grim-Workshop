#version 150 core

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec3 inPosition;
in vec4 inColor;
in vec2 inTexCoord;

out vec4 color;
out vec2 texCoord;

void main()
{
    color = inColor;
    texCoord = inTexCoord;
    gl_Position = proj * view * model * vec4(inPosition, 1.0);
}