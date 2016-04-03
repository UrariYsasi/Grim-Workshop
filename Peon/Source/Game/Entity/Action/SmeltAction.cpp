#include "PCH.hpp"
#include "SmeltAction.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "DepositAction.hpp"
#include "WithdrawAction.hpp"
#include "../Monster.hpp"
#include "../Forge.hpp"
#include "../../Item/Inventory.hpp"

SmeltAction::SmeltAction(Monster* owner, Forge* forge) :
    Action(owner, SMELT_ACTION, "Smelt"),
    m_forge(forge),
    m_forgeTime(5)
{
}

SmeltAction::~SmeltAction()
{
}

void SmeltAction::Update(float deltaTime)
{
    // Do we have enough ore?
    Inventory* inventory = m_owner->GetInventory();
    int quantity = inventory->CountItem(ItemType::IRON_ORE);
    if (quantity < 3)
    {
        // We don't have enough ore... Go grab some.
        m_owner->PushAction(std::make_unique<WithdrawAction>(m_owner, ItemType::IRON_ORE, 3));
        return;
    }

    // Check if we are within range
    glm::vec2 targetCenter = m_forge->GetPosition();
    glm::vec2 monsterCenter = m_owner->GetPosition();
    double distance = glm::distance(monsterCenter, targetCenter);

    if (distance <= MIN_DISTANCE)
    {
        // We are close enough.
        if (!m_timer.IsStarted())
        {
            //m_forgeTime = Random::Generate(700, 1500);
            m_timer.Start();
        }
        else
        {
            if (m_timer.GetTime() > m_forgeTime)
            {
                m_timer.Stop();

                //m_owner->GetGame()->PlaySound("woodcutting_00");
                inventory->RemoveItem(ItemType::IRON_ORE, 3);
                inventory->GiveItem(ItemType::IRON_BAR, 1);
                m_owner->PushAction(std::make_unique<DepositAction>(m_owner, ItemType::IRON_BAR, 1));
            }
        }
    }
    else
    {
        // We aren't close enough. Move to the resource.
        m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_forge->GetPosition()));
        return;
    }
}
