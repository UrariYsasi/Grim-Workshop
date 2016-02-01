#pragma once
#include "Resource.hpp"

class Rock : public Resource
{
public:
    Rock(Game* game, Vector2D position);
    virtual ~Rock();

    virtual void Update(double deltaTime);
    virtual void Render();
};
