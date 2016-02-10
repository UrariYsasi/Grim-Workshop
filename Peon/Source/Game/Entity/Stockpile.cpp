#include "PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Stockpile::Stockpile(Game* game, Vector2D position) :
    Prop(game, position)
{
    m_origin = Vector2D(16, 16);
    m_hitBox = Rectangle(-16, -16, 32, 32);
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
    renderer->RenderSprite("bonfire_4", 0, 0, (int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y);
}
