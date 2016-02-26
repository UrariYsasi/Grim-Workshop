#include "PCH.hpp"
#include "SacrificeAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../../Map/Map.hpp"
#include "../Altar.hpp"

SacrificeAction::SacrificeAction(Monster* owner, Altar* altar) :
    Action(owner, SACRIFICE_ACTION, "Sacrifice"),
    m_altar(altar)
{
}

SacrificeAction::~SacrificeAction()
{
}

void SacrificeAction::Update(double deltaTime)
{
    // Get the offering
    Entity* offering = m_owner->GetHeldEntity();
    if (offering == nullptr)
    {
        Complete();
        return;
    }

    // Check if we are in range of the altar
    Vector2D targetCenter = m_altar->GetPosition();
    Vector2D monsterCenter = m_owner->GetPosition();
    double distance = Vector2D::Distance(monsterCenter, targetCenter);

    if (distance <= MIN_DISTANCE)
    {
        // Drop the offering
        m_owner->DropHeldEntity();

        offering->Delete();

        m_owner->GetGame()->PlaySound("monk_spawn");

        m_owner->GetGame()->GetMap()->SpawnPeon(2, m_altar->GetPosition());

        // Complete the action
        Complete();
    }
    else
    {
        // We aren't close enough. Move.
        m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_altar->GetPosition()));
    }
}
