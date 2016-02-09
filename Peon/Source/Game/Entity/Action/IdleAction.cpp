#include "PCH.hpp"
#include "IdleAction.hpp"
#include "../../../Engine/Vector2D.hpp"
#include "MoveAction.hpp"
#include "../Monster.hpp"

IdleAction::IdleAction(Monster* owner) :
    Action(owner, "Idle"),
    m_waitTime(5)
{
}

IdleAction::~IdleAction()
{
}

void IdleAction::Update(double deltaTime)
{
    if (!m_timer.IsStarted())
    {
        m_waitTime = (int)Random::Generate(1000, 10000);
        m_timer.Start();
    }
    else
    {
        if (m_timer.GetTime() > m_waitTime)
        {
            m_timer.Stop();

            double randX = Random::Generate(-32, 32);
            double randY = Random::Generate(-32, 32);
            Vector2D wanderDestination = m_owner->GetPosition() + Vector2D(randX, randY);

            m_owner->PushAction(std::make_unique<MoveAction>(m_owner, wanderDestination));
        }
    }
}
