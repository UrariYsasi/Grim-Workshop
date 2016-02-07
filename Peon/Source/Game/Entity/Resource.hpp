#pragma once
#include "Prop.hpp"

class Monster;

class Resource : public Prop
{
public:
    Resource(Game* game, Vector2D position);
    virtual ~Resource();

    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;
};
