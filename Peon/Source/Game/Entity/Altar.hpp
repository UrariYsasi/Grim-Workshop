#pragma once
#include "Prop.hpp"

class Altar : public Prop
{
public:
    Altar(Game* game, const glm::vec2& position);
    virtual ~Altar();

    virtual void Update(double deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};
