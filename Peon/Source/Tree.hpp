#pragma once
#include "PCH.hpp"
#include "Entity.hpp"

class Tree : public Entity
{
public:
    Tree(Game* game, const Vector2D& position);
    ~Tree();

    virtual void Update();
    virtual void Render();
};