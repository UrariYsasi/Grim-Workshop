#include "../../PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"

Stockpile::Stockpile(Game* game, Vector2D position) :
    Prop(game, position)
{
}

Stockpile::~Stockpile()
{
}

void Stockpile::Update()
{

}

void Stockpile::Render()
{
    m_game->RenderSprite("bonfire_4", 0, 0, m_position.GetX(), m_position.GetY(), 32, 32);
}
