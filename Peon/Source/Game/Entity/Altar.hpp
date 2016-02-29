#pragma once
#include "Prop.hpp"

class Altar : public Prop
{
public:
    Altar(Game* game, Vector2D position);
    virtual ~Altar();

    virtual void Update(double deltaTime);
    virtual void Render();
};
