#pragma once
#include "Monster.hpp"

class Spider : public Monster
{
public:
    Spider(Game* game, const glm::vec2& position);
    virtual ~Spider();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};
