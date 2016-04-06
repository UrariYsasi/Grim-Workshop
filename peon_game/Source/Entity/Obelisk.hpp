#pragma once
#include "Prop.hpp"

class Obelisk : public Prop
{
public:
    Obelisk(Game* game, const glm::vec2& position);
    virtual ~Obelisk();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};
