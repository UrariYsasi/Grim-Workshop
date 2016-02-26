#include "PCH.hpp"
#include "Monster.hpp"
#include "../Game.hpp"
#include "Action/IdleAction.hpp"
#include "Action/AttackAction.hpp"

Monster::Monster(Game* game, Vector2D position, int entityID) :
    Entity(game, position, entityID),
    m_heldEntity(nullptr),
    m_moveSpeed(64)
{
    m_moveSpeed += (int)Random::Generate(-10, 10);
}

Monster::~Monster()
{
    m_actionStack.clear();
}

Inventory* Monster::GetInventory()
{
    return &m_inventory;
}

int Monster::GetMoveSpeed()
{
    return m_moveSpeed;
}

void Monster::Update(double deltaTime)
{
    if (IsDead())
    {
        return;
    }

    CleanActionStack();

    if (m_actionStack.size() == 0)
    {
        std::unique_ptr<Action> action = std::make_unique<IdleAction>(this);
        m_actionStack.push_back(std::move(action));
    }

    // Update the current action
    if(m_actionStack.back() != nullptr)
    {
        if (!m_actionStack.back()->IsComplete())
        {
            m_actionStack.back()->Update(deltaTime);
        }
    }

    if (m_heldEntity != nullptr)
    {
        m_heldEntity->SetPosition(m_position + Vector2D(0, -12));
    }
}

void Monster::PushAction(std::unique_ptr<Action> action)
{
    m_actionStack.push_back(std::move(action));
}

void Monster::ClearActionStack()
{
    std::list< std::unique_ptr<Action> >::const_iterator it;
    for (it = m_actionStack.begin(); it != m_actionStack.end(); it++)
    {
        (*it)->Complete();
    }
}

void Monster::CleanActionStack()
{
    for (auto it = m_actionStack.begin(); it != m_actionStack.end(); it++)
    {
        if ((*it)->IsComplete())
        {
            m_actionStack.erase(it++);
        }
    }
}

Action* Monster::FindAction(int actionID)
{
    for (auto it = m_actionStack.begin(); it != m_actionStack.end(); it++)
    {
        Action* action = (*it).get();
        if (action->GetActionID() == actionID)
        {
            return action;
        }
    }

    return nullptr;
}

void Monster::SetHeldEntity(Entity* ent)
{
    ent->SetHeld(true);
    m_heldEntity = ent;
}

Entity* Monster::GetHeldEntity()
{
    return m_heldEntity;
}

void Monster::DropHeldEntity()
{
    if (m_heldEntity != nullptr)
    {
        m_heldEntity->SetHeld(false);
        m_heldEntity = nullptr;
    }
}