#pragma once
#include "Resource.hpp"

class Rock : public Resource
{
public:
    Rock(Game* game, const glm::vec2& position);
    virtual ~Rock();

    virtual ItemType GetItem() const;

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};
