#pragma once
#include "PCH.hpp"
#include "Entity.hpp"

class Stone : public Entity
{
public:
    Stone(Game* game, const Vector2D& position);
    ~Stone();

    virtual void Update();
    virtual void Render();
};