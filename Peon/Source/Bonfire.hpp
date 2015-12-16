#pragma once
#include "PCH.hpp"
#include "Entity.hpp"

class Bonfire : public Entity
{
public:
    Bonfire(Game* game, const Vector2D& position);
    ~Bonfire();

    virtual void Update();
    virtual void Render();
};