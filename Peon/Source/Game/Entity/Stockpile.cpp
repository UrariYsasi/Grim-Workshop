#include "PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Stockpile::Stockpile(Game* game, Vector2D position) :
    Prop(game, position)
{
}

Stockpile::~Stockpile()
{
}

Inventory* Stockpile::GetInventory()
{
    return &m_inventory;
}

void Stockpile::Update(double deltaTime)
{
}

void Stockpile::Render()
{
    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("bonfire_4", 0, 0, (int)m_position.x, (int)m_position.y, (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y);
}
