#pragma once
#include "Prop.hpp"

class Forge : public Prop
{
public:
    Forge(Game* game, const Vector2D& position);
    virtual ~Forge();

    virtual void Update(double deltaTime);
    virtual void Render();
};
