#include "PCH.hpp"
#include "Peon.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "../../Engine/Renderer.hpp"

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
    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("peon", 0, 0, (int)m_position.x, (int)m_position.y, 32, 32);
}

