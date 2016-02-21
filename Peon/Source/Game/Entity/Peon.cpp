#include "PCH.hpp"
#include "Peon.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "Action/IdleAction.hpp"
#include "../../Engine/Renderer.hpp"

Peon::Peon(Game* game, Vector2D position) :
    Monster(game, position, PEON)
{
    m_origin = Vector2D(16, 16);
    m_hitBox = Rectangle(-4, 0, 8, 16);
}

Peon::~Peon()
{
}

void Peon::Update(double deltaTime)
{
    // If this Peon has no actions, add an IdleAction.
    if (m_actionStack.size() == 0)
    {
        std::unique_ptr<Action> action = std::make_unique<IdleAction>(this);
        m_actionStack.push_back(std::move(action));
    }

    Monster::Update(deltaTime);
}

void Peon::Render()
{
    Renderer* renderer = m_game->GetRenderer();

    if (m_hp > 0)
    {
        renderer->RenderSprite("peon", 0, 0, (int)(m_position.x + m_positionOffset.x - m_origin.x), (int)(m_position.y + m_positionOffset.y - m_origin.y), 32, 32);
    }
    else
    {
        renderer->RenderSprite("peon", 1, 0, (int)(m_position.x + m_positionOffset.x - m_origin.x), (int)(m_position.y + m_positionOffset.y - m_origin.y), 32, 32);
    }

    if (m_inventory.CountItem(ItemType::WOOD) > 0)
    {
        renderer->RenderSprite("peon", 1, 2, (int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), 32, 32);
    }

    if (m_inventory.CountItem(ItemType::STONE) > 0)
    {
        renderer->RenderSprite("peon", 0, 2, (int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), 32, 32);
    }

    if (m_inventory.CountItem(ItemType::COAL) > 0)
    {
        renderer->RenderSprite("peon", 0, 2, (int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), 32, 32);
    }

    if (m_inventory.CountItem(ItemType::IRON_ORE) > 0)
    {
        renderer->RenderSprite("peon", 0, 2, (int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), 32, 32);
    }

    Entity::Render();
}

