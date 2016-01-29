#pragma once
#include "Entity.hpp"

class Prop : public Entity
{
public:
    Prop(Game* game, Vector2D position);
    virtual ~Prop();

    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;
};
