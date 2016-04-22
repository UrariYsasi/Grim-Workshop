#include "PCH.hpp"
#include "IdleAction.hpp"
#include "MoveAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "../../World/World.hpp"

IdleAction::IdleAction(Monster* owner) :
    Action(owner, IDLE_ACTION, "Idle"),
    m_waitTimeSeconds(5.0f)
{
}

IdleAction::~IdleAction()
{
}

void IdleAction::Update(float deltaTime)
{
    if (!m_timer.IsStarted())
    {
        if (m_owner->GetEntityID() == ENT_MONSTER_SPIDER_QUEEN)
        {
            m_waitTimeSeconds = 1;
        }
        else
        {
            m_waitTimeSeconds = static_cast<uint16_t>(grim::utility::Random::Generate(1, 10));
        }

        m_timer.Start();
    }
    else
    {
        if (m_timer.GetTimeInSeconds() > m_waitTimeSeconds)
        {
            m_timer.Stop();

            double randX = grim::utility::Random::Generate(-32.0, 32.0);
            double randY = grim::utility::Random::Generate(-32.0, 32.0);
            glm::vec2 wanderDestination = m_owner->GetPosition() + glm::vec2(randX, randY);
            //if (m_owner->GetGame()->GetWorld()->IsPassable(wanderDestination))
            //{
            m_owner->PushAction(std::make_unique<MoveAction>(m_owner, wanderDestination));
            //}
        }
    }
}
