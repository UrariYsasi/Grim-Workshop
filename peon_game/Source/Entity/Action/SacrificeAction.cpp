#include "PCH.hpp"
#include "SacrificeAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../../World/World.hpp"
#include "../Altar.hpp"

SacrificeAction::SacrificeAction(Monster* owner, Altar* altar) :
    Action(owner, SACRIFICE_ACTION, "Sacrifice"),
    m_altar(altar)
{
}

SacrificeAction::~SacrificeAction()
{
}

void SacrificeAction::Update(float deltaTime)
{
    // Get the offering
    Entity* offering = m_owner->GetHeldEntity();
    if (offering == nullptr)
    {
        Complete();
        return;
    }

    // Check if we are in range of the altar
    glm::vec2 targetCenter = m_altar->GetPosition();
    glm::vec2 monsterCenter = m_owner->GetPosition();
    double distance = glm::distance(monsterCenter, targetCenter);

    if (distance <= MIN_DISTANCE)
    {
        // Drop the offering
        m_owner->DropHeldEntity();

        offering->Delete();

        m_owner->GetGame()->GetAudio()->PlaySound("sacrifice_04");

        m_owner->GetGame()->GetWorld()->Spawn(ENT_PEON, m_altar->GetPosition());

        // Complete the action
        Complete();
    }
    else
    {
        // We aren't close enough. Move.
        m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_altar->GetPosition()));
    }
}
