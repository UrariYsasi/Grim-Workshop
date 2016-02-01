#pragma once
#include "Monster.hpp"

class Peon : public Monster
{
public:
    Peon(Game* game, Vector2D position);
    virtual ~Peon();

    virtual void Update(double deltaTime);
    virtual void Render();
};
