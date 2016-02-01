#include "PCH.hpp"
#include "Peon.hpp"
#include "../Game.hpp"
#include "Action\MoveAction.hpp"

Peon::Peon(Game* game, Vector2D position) :
    Monster(game, position)
{
}

Peon::~Peon()
{
}

void Peon::Update(double deltaTime)
{
    Monster::Update(deltaTime);
}

void Peon::Render()
{
    m_game->RenderSprite("peon", 0, 0, m_position.x, m_position.y, 32, 32);
}

