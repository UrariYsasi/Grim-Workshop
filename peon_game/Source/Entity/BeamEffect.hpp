#pragma once
#include "Entity.hpp"

class BeamEffect : public Entity
{
public:
    BeamEffect(Game* game, const glm::vec2& position);
    virtual ~BeamEffect();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};
