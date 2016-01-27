#include "../../../PCH.hpp"
#include "DumpAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"

DumpAction::DumpAction(Monster* owner) :
    Action(owner, "Dump")
{
}

DumpAction::~DumpAction()
{
}

void DumpAction::Update()
{
    // If we don't have a target stockpile, find one
    if (m_target == nullptr)
    {
        m_target = m_owner->GetGame()->FindStockpile();
    }
    else
    {
        // Check if we are in range of the stockpile
        Vector2D targetCenter = m_target->GetPositionCenter();
        Vector2D monsterCenter = m_owner->GetPositionCenter();
        double distance = Vector2D::Distance(monsterCenter, targetCenter);
        if (distance <= 10.0)
        {
            // Add resources to the stockpile
            // TODO make this take resources from monster inventory
            m_owner->GetGame()->AddResources(5);
            m_isComplete = true;
        }
        else
        {
            // We aren't close enough. Move to the resource.
            m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_target->GetPosition()));
        }
    }
}
