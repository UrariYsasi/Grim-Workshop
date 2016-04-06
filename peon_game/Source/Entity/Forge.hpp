#pragma once
#include "Prop.hpp"

class Forge : public Prop
{
public:
    Forge(Game* game, const glm::vec2& position);
    virtual ~Forge();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};
