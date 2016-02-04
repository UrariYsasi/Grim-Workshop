#include "PCH.hpp"
#include "DumpAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../../Item/Item.hpp"
#include "../../Item/Inventory.hpp"
#include "../Stockpile.hpp"

DumpAction::DumpAction(Monster* owner, const ItemType& dumpType) :
    Action(owner, "Dump"),
    m_dumpType(dumpType)
{
}

DumpAction::~DumpAction()
{
}

void DumpAction::Update(double deltaTime)
{
    // If we don't have a target stockpile, find one
    if (m_target == nullptr)
    {
        m_target = m_owner->GetGame()->FindStockpile();
        
        if (m_target == nullptr)
        {
            // There was no stockpile found. Stop working.
            m_owner->ClearActions();
        }
    }
    else
    {
        // Check if we are in range of the stockpile
        Vector2D targetCenter = m_target->GetPositionCenter();
        Vector2D monsterCenter = m_owner->GetPositionCenter();
        double distance = Vector2D::Distance(monsterCenter, targetCenter);

        if (distance <= MIN_DUMP_DISTANCE)
        {
            // Add resources to the stockpile
            int resourceCount = m_owner->GetInventory()->ItemCount(m_dumpType);
            m_owner->GetInventory()->RemoveItem(m_dumpType, resourceCount);
            m_target->GetInventory()->AddItem(m_dumpType, resourceCount);

            // Complete the action
            Complete();
        }
        else
        {
            // We aren't close enough. Move to the resource.
            m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_target->GetPosition()));
        }
    }
}
