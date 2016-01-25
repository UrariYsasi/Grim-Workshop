#pragma once
#include "../../PCH.hpp"
#include "Monster.hpp"

class Peon : public Monster
{
public:
    Peon(Game* game, Vector2D position);
    virtual ~Peon();

    virtual void Update();
    virtual void Render();
};
