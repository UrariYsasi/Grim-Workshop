#include "PCH.hpp"
#include "GatherAction.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "DepositAction.hpp"
#include "../Monster.hpp"
#include "../Resource.hpp"
#include "../../Item/Inventory.hpp"

GatherAction::GatherAction(Monster* owner, Resource* target) :
    Action(owner, "Gather"),
    m_target(target),
    m_gatherTime(3)
{
}

GatherAction::~GatherAction()
{
}

void GatherAction::Update(double deltaTime)
{
    // Check if we are in range of the resource
    Vector2D targetCenter = m_target->GetPositionCenter();
    Vector2D monsterCenter = m_owner->GetPositionCenter();
    double distance = Vector2D::Distance(monsterCenter, targetCenter);

    if (distance <= MIN_GATHER_DISTANCE)
    {
        // We are close enough. We can start gathering.
        if (!m_timer.IsStarted())
        {
            m_gatherTime = Random::Generate(700, 1500);
            m_timer.Start();
        }
        else
        {
            if (m_timer.GetTime() > m_gatherTime)
            {
                m_timer.Stop();

                m_owner->GetGame()->PlaySound("woodcutting_00"); // TODO different sounds
                ItemType item = m_target->GetItem();
                m_owner->GetInventory()->GiveItem(item, (int)Random::Generate(1, 5));
                m_owner->PushAction(std::make_unique<DepositAction>(m_owner, item));
            }
        }
    }
    else
    {
        // We aren't close enough. Move to the resource.
        m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_target->GetPosition()));
    }
}
