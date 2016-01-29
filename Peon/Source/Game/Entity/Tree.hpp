#pragma once
// Tyren Review: Never include PCH in headers
#include "../../PCH.hpp"

#include "Resource.hpp"

class Tree : public Resource
{
public:
    Tree(Game* game, Vector2D position);
    virtual ~Tree();

    virtual void Update();
    virtual void Render();
};
