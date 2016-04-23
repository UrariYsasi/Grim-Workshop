#pragma once
#include "Entity.hpp"

class Altar : public Entity
{
public:
    Altar(Game* game, const glm::vec2& position);
    virtual ~Altar();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};
