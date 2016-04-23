#pragma once
#include "Entity.hpp"

class Obelisk : public Entity
{
public:
    Obelisk(Game* game, const glm::vec2& position);
    virtual ~Obelisk();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);

    void ConsumeEntity(Entity* ent);
};
