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

    Material() :
        Material(nullptr, nullptr, Color(1.0f, 1.0f, 1.0f))
    {
    }

    Material(Texture* texture, ShaderProgram* shaderProgram) :
        Material(texture, shaderProgram, Color(1.0f, 1.0f, 1.0f))
    {
    }

    Material(Texture* texture, ShaderProgram* shaderProgram, Color color) :
        texture(texture),
        shaderProgram(shaderProgram),
        color(color)
    {
    }
};

}

}