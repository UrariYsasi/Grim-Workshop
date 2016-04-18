#pragma once

namespace grim
{

namespace graphics
{

/*
    A 2D, renderable sprite.
*/
struct Sprite
{
    grim::graphics::Texture* spriteSheet;
    grim::graphics::ShaderProgram* shaderProgram;
    grim::graphics::Color color;
    uint16_t width;
    uint16_t height;
    uint16_t frame;
    uint16_t geometryWidth;
    uint16_t geometryHeight;

    Sprite(grim::graphics::Texture* spriteSheet, grim::graphics::ShaderProgram* shaderProgram, uint16_t width, uint16_t height, uint16_t frame, const grim::graphics::Color& color = graphics::Color(1, 1, 1, 1)) :
        spriteSheet(spriteSheet),
        shaderProgram(shaderProgram),
        width(width),
        height(height),
        frame(frame),
        color(color),
        geometryWidth(width),
        geometryHeight(height)
    {
    }
};

}

}