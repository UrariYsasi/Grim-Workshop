#include "PCH.hpp"
#include "GrassTile.hpp"
#include "../Game.hpp"

GrassTile::GrassTile(Game* game, const Vector2D& position) :
    Tile(game, position, 0, 0)
{
}

GrassTile::~GrassTile()
{
}

void GrassTile::Render()
{
    Tile::Render();
}