#include "PCH.hpp"
#include "Stone.hpp"
#include "Game.hpp"

Stone::Stone(Game* game, const Vector2D& position) :
    Entity(game, position)
{
}

Stone::~Stone()
{
}

void Stone::Update()
{
}

void Stone::Render()
{
    m_game->RenderTexture("stone", m_position.GetX(), m_position.GetY(), 32, 32);
}