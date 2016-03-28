#pragma once

namespace grim
{

/*
    A 2D, renderable sprite.
*/
struct Sprite
{
    grim::Texture* spriteSheet;
    grim::ShaderProgram* shaderProgram;
    grim::Color color;
    uint16_t width;
    uint16_t height;
    uint16_t frame;

    Sprite(grim::Texture* spriteSheet, grim::ShaderProgram* shaderProgram, uint16_t width, uint16_t height, uint16_t frame, const grim::Color& color = grim::Color(1, 1, 1, 1)) :
        spriteSheet(spriteSheet),
        shaderProgram(shaderProgram),
        width(width),
        height(height),
        frame(frame),
        color(color)
    {
    }
};

}