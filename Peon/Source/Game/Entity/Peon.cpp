#include "PCH.hpp"
#include "Peon.hpp"
#include "../Game.hpp"
#include "Action/MoveAction.hpp"
#include "Action/IdleAction.hpp"
#include "Action/AttackAction.hpp"
#include "../../Engine/Renderer.hpp"
#include "Orc.hpp"
#include "../Map/Map.hpp"

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
    Monster::Update(deltaTime);

    Map* map = m_game->GetMap();

    // If we don't have an attack action already
    AttackAction* attackAction = dynamic_cast<AttackAction*>(FindAction(ATTACK_ACTION));
    if (attackAction == nullptr)
    {
        // Search for some Orcs
        Rectangle searchRect(m_position.x - 64, m_position.y - 64, 128, 128);
        std::list<Entity*> orcs = map->GetEntitiesInRectangle(ORC, searchRect);
        if (orcs.size() > 0)
        {
            // Found some orcs. Go attack them.
            ClearActionStack();
            Entity* orcEnt = orcs.back();
            PushAction(std::make_unique<AttackAction>(this, orcEnt));
        }
    }

    // If this Peon has no actions, add an IdleAction.
    if (m_actionStack.size() == 0)
    {
        std::unique_ptr<Action> action = std::make_unique<IdleAction>(this);
        m_actionStack.push_back(std::move(action));
    }
}

void Peon::Render()
{
    Renderer* renderer = m_game->GetRenderer();

    if (!IsDead())
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