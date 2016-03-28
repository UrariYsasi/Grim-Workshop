#pragma once
#include "Prop.hpp"

class Forge : public Prop
{
public:
    Forge(Game* game, const glm::vec2& position);
    virtual ~Forge();

    virtual void Update(double deltaTime);
    virtual void Render(grim::SpriteBatch& spriteBatch);
};
