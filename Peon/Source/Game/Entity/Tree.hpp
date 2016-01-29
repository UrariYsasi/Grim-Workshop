#pragma once
#include "Resource.hpp"

class Tree : public Resource
{
public:
    Tree(Game* game, Vector2D position);
    virtual ~Tree();

    virtual void Update();
    virtual void Render();
};
