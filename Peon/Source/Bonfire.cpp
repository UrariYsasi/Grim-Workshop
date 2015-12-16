#include "PCH.hpp"
#include "Bonfire.hpp"
#include "Game.hpp"

Bonfire::Bonfire(Game* game, const Vector2D& position) :
    Entity(game, position)
{
}

Bonfire::~Bonfire()
{
}

void Bonfire::Update()
{

}

void Bonfire::Render()
{
    m_game->RenderTexture("bonfire_4", m_position.GetX(), m_position.GetY(), 32, 32);
}