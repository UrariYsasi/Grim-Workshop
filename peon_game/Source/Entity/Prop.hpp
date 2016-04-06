#pragma once
#include "Entity.hpp"

class Prop : public Entity
{
public:
    Prop(Game* game, const glm::vec2& position, int entityID);
    virtual ~Prop();

    virtual void Update(float deltaTime) = 0;
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch) = 0;
};
