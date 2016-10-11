// TODO:
// Refactor this schnizz

#pragma once

namespace grim::assets
{

struct Material
{
    Texture* texture;
    graphics::ShaderProgram* shaderProgram;
    graphics::Color color;

    Material() :
        Material(nullptr, nullptr, graphics::Color(1.0f, 1.0f, 1.0f))
    {
    }

    Material(Texture* texture, graphics::ShaderProgram* shaderProgram) :
        Material(texture, shaderProgram, graphics::Color(1.0f, 1.0f, 1.0f))
    {
    }

    Material(Texture* texture, graphics::ShaderProgram* shaderProgram, graphics::Color color) :
        texture(texture),
        shaderProgram(shaderProgram),
        color(color)
    {
    }
};

}