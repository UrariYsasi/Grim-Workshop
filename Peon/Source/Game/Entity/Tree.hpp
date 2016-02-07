#pragma once
#include "Resource.hpp"

class Tree : public Resource
{
public:
    Tree(Game* game, Vector2D position);
    virtual ~Tree();

    virtual ItemType GetItem() const;

    virtual void Update(double deltaTime);
    virtual void Render();
};
