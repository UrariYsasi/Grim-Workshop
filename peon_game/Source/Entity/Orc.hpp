#pragma once
#include "Monster.hpp"

class Orc : public Monster
{
public:
    Orc(Game* game, const glm::vec2& position);
    virtual ~Orc();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};