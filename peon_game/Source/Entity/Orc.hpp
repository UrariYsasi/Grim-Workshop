#pragma once
#include "Monster.hpp"

class Orc : public Monster
{
public:
    Orc(Game* game, const glm::vec3& position);
    virtual ~Orc();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};
