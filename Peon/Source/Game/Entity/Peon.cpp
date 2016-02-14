#include "PCH.hpp"
#include "Peon.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "../../Engine/Renderer.hpp"

Peon::Peon(Game* game, Vector2D position) :
    Monster(game, position)
{
    m_origin = Vector2D(16, 16);
    m_hitBox = Rectangle(-4, 0, 8, 16);
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
    renderer->RenderSprite("peon", 0, 0, (int)(m_position.x + m_positionOffset.x - m_origin.x), (int)(m_position.y + m_positionOffset.y - m_origin.y), 32, 32);

    // Held item
    //renderer->RenderSprite("peon", 1, 2, (int)m_position.x, (int)m_position.y, 32, 32);

    Entity::Render();
}

