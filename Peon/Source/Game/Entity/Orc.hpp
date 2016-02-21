#pragma once
#include "Monster.hpp"

class Orc : public Monster
{
public:
    Orc(Game* game, Vector2D position);
    virtual ~Orc();

    virtual void Update(double deltaTime);
    virtual void Render();
};
