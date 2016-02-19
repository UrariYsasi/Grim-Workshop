#include "PCH.hpp"
#include "WithdrawAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../../Item/Inventory.hpp"
#include "../Stockpile.hpp"
#include "../../Map/Map.hpp"

WithdrawAction::WithdrawAction(Monster* owner, ItemType withdrawItem, const int& quantity) :
    Action(owner, "Withdraw"),
    m_quantity(quantity),
    m_withdrawItem(withdrawItem)
{
}

WithdrawAction::~WithdrawAction()
{
}

void WithdrawAction::Update(double deltaTime)
{
    // If we don't have a target stockpile, find one
    if (m_target == nullptr)
    {
        m_target = m_owner->GetGame()->GetMap()->FindStockpile();
        
        if (m_target == nullptr)
        {
            // There was no stockpile found. Stop working.
            m_owner->ClearActionStack();
        }
    }
    else
    {
        // Check if we are in range of the stockpile
        Vector2D targetCenter = m_target->GetPositionCenter();
        Vector2D monsterCenter = m_owner->GetPositionCenter();
        double distance = Vector2D::Distance(monsterCenter, targetCenter);

        if (distance <= MIN_DISTANCE)
        {
            if (m_target->GetInventory()->RemoveItem(m_withdrawItem, m_quantity))
            {
                m_owner->GetInventory()->GiveItem(m_withdrawItem, m_quantity);
            }
            else
            {
                // There wasn't any of the item to take.
                m_owner->ClearActionStack();
            }

            // Complete the action
            Complete();
        }
        else
        {
            // We aren't close enough. Move to the stockpile.
            m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_target->GetPosition()));
            return;
        }
    }
}
