#pragma once
#include "Prop.hpp"

class Obelisk : public Prop
{
public:
    Obelisk(Game* game, Vector2D position);
    virtual ~Obelisk();

    virtual void Update(double deltaTime);
    virtual void Render();
};
