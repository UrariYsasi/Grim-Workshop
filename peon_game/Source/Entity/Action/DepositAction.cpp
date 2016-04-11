#include "PCH.hpp"
#include "DepositAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../../Item/Inventory.hpp"
#include "../Stockpile.hpp"
#include "../../World/World.hpp"
#include "../Obelisk.hpp"

DepositAction::DepositAction(Monster* owner) :
    Action(owner, DEPOSIT_ACTION, "Deposit"),
    m_obelisk(nullptr)
{
}

DepositAction::~DepositAction()
{
}

void DepositAction::Update(float deltaTime)
{
    // Get the item to deposit
    Entity* offering = m_owner->GetHeldEntity();
    if (offering == nullptr)
    {
        Complete();
        return;
    }

    // Find the obelisk
    if (m_obelisk == nullptr)
    {
        Obelisk* obelisk = dynamic_cast<Obelisk*>(m_owner->GetGame()->GetWorld()->FindEntity(OBELISK));
        if (obelisk == nullptr)
        {
            Complete();
            return;
        }

        m_obelisk = obelisk;
    }

    // Check if we are in range of the obelisk
    glm::vec2 targetPosition = m_obelisk->GetPosition();
    glm::vec2 ownerPosition = m_owner->GetPosition();
    float distance = glm::distance(ownerPosition, targetPosition);

    if (distance <= MIN_DISTANCE)
    {
        // Drop the payload
        m_owner->DropHeldEntity();

        uint8_t rand = static_cast<uint8_t>(std::round(grim::utility::Random::Generate(1.3, 4.4)));
        m_owner->GetGame()->GetAudio()->PlaySound("sacrifice_0" + std::to_string(rand));

        m_obelisk->ConsumeEntity(offering);

        // Complete the action
        Complete();
    }
    else
    {
        // We aren't close enough. Move.
        std::unique_ptr<MoveAction> moveAction = std::make_unique<MoveAction>(m_owner, m_obelisk->GetPosition());
        moveAction->SetMinimumRange(MIN_DISTANCE);
        m_owner->PushAction(std::move(moveAction));
    }
}
