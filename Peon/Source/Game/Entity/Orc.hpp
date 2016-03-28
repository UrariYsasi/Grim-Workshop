#pragma once
#include "Monster.hpp"

class Orc : public Monster
{
public:
    Orc(Game* game, const glm::vec2& position);
    virtual ~Orc();

    virtual void Update(double deltaTime);
    virtual void Render(grim::SpriteBatch& spriteBatch);
};
