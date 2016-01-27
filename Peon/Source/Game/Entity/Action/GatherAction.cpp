#include "../../../PCH.hpp"
#include "GatherAction.hpp"
#include "../../../Engine/Vector2D.hpp"
#include "MoveAction.hpp"
#include "DumpAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"

GatherAction::GatherAction(Monster* owner, Resource* target) :
    Action(owner, "Gather"),
    m_target(target),
    m_gatherTime(3)
{
}

GatherAction::~GatherAction()
{
}

void GatherAction::Update()
{
    // Check if we are in range of the resource
    Vector2D targetCenter = m_target->GetPositionCenter();
    Vector2D monsterCenter = m_owner->GetPositionCenter();
    double distance = Vector2D::Distance(monsterCenter, targetCenter);
    if (distance <= 10.0)
    {
        // We are close enough. We can start gathering.
        if (!m_timer.IsStarted())
        {
            m_gatherTime = std::rand() % 1000 + 700;
            m_timer.Start();
        }
        else
        {
            if (m_timer.GetTime() > m_gatherTime)
            {
                m_timer.Stop();
                m_owner->GetGame()->PlaySound("woodcutting_00");
                // Add resources to our inventory
                m_owner->PushAction(std::make_unique<DumpAction>(m_owner));
            }

            // If we are carrying enough resources, go dump them at base
        }
    }
    else
    {
        // We aren't close enough. Move to the resource.
        m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_target->GetPosition()));
    }
}
