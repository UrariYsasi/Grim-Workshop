#pragma once
#include "Resource.hpp"

class Tree : public Resource
{
public:
    Tree(Game* game, const glm::vec2& position);
    virtual ~Tree();

    virtual ItemType GetItem() const;

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
};
