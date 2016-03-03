#include "PCH.hpp"
#include "DepositAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../../Item/Inventory.hpp"
#include "../Stockpile.hpp"
#include "../../World/World.hpp"

DepositAction::DepositAction(Monster* owner, ItemType dumpItem, const int& quantity) :
    Action(owner, DEPOSIT_ACTION, "Deposit"),
    m_quantity(quantity),
    m_dumpItem(dumpItem)
{
}

DepositAction::~DepositAction()
{
}

void DepositAction::Update(double deltaTime)
{
    // If we don't have a target stockpile, find one
    if (m_target == nullptr)
    {
        Entity* ent = m_owner->GetGame()->GetWorld()->FindEntity(STOCKPILE);
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
        glm::vec2 targetCenter = m_target->GetPosition();
        glm::vec2 monsterCenter = m_owner->GetPosition();
        double distance = glm::distance(monsterCenter, targetCenter);

        if (distance <= MIN_DISTANCE)
        {
            // If we gave a negative quantity, that means to deposit all of that item
            int count;
            if (m_quantity < 0)
            {
                count = m_owner->GetInventory()->CountItem(m_dumpItem);
            }
            else
            {
                count = m_quantity;
            }

            // Add resources to the stockpile
            if (m_owner->GetInventory()->RemoveItem(m_dumpItem, count))
            {
                m_target->GetInventory()->GiveItem(m_dumpItem, count);
            }

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
