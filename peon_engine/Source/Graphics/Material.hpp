#pragma once

namespace grim
{

namespace graphics
{

struct Material
{
    Texture* texture;
    ShaderProgram* shaderProgram;
    Color color;

    Material(Texture* texture, ShaderProgram* shaderProgram, Color color) :
        texture(texture),
        shaderProgram(shaderProgram),
        color(color)
    {
    }

    Material(Texture* texture, ShaderProgram* shaderProgram) :
        texture(texture),
        shaderProgram(shaderProgram),
        color(1.0f, 1.0f, 1.0f)
    {
    }
};

}

}