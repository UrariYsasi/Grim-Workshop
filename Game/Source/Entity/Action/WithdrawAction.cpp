#include "PCH.hpp"
#include "WithdrawAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../../Item/Inventory.hpp"
#include "../Stockpile.hpp"
#include "../../World/World.hpp"

WithdrawAction::WithdrawAction(Monster* owner, ItemType withdrawItem, const int& quantity) :
    Action(owner, WITHDRAW_ACTION, "Withdraw"),
    m_quantity(quantity),
    m_withdrawItem(withdrawItem),
    m_target(nullptr)
{
}

WithdrawAction::~WithdrawAction()
{
}

void WithdrawAction::Update(float deltaTime)
{
    // If we don't have a target stockpile, find one
    if (m_target == nullptr)
    {
        Entity* ent = m_owner->GetGame()->GetWorld()->FindEntity(EntityID::STRUCTURE_STOCKPILE);
        m_target = dynamic_cast<Stockpile*>(ent);
        
        if (m_target == nullptr)
        {
            // There was no stockpile found. Stop working.
            m_owner->ClearActionStack();
        }
    }
    else
    {
        // Check if we are in range of the stockpile
        glm::vec3 targetCenter = m_target->GetTransform().position;;
        glm::vec3 monsterCenter = m_owner->GetTransform().position;;
        double distance = glm::distance(monsterCenter, targetCenter);

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
            m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_target->GetTransform().position));
            return;
        }
    }
}
