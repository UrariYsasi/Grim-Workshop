#pragma once
#include "Tile.hpp"

class GrassTile : public Tile
{
public:
    GrassTile(Game* game, const Vector2D& position);
    virtual ~GrassTile();

    virtual void Render();
};