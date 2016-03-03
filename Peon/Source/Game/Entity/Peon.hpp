#pragma once
#include "Monster.hpp"

class Peon : public Monster
{
public:
    Peon(Game* game, const glm::vec2& position);
    virtual ~Peon();

    virtual void Update(double deltaTime);
    virtual void Render();
};
