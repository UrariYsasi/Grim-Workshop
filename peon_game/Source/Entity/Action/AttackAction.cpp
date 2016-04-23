#include "PCH.hpp"
#include "AttackAction.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../Monster.hpp"
#include "../Peon.hpp"

AttackAction::AttackAction(Monster* owner, Entity* target) :
    Action(owner, ACTION_ATTACK, "Attack"),
    m_target(target),
    m_attackSpeedSeconds(2)
{
    m_attackSpeedSeconds += grim::utility::Random::Generate(-1.0f, 1.0f);
}

AttackAction::~AttackAction()
{
}

void AttackAction::Update(float deltaTime)
{
    if (m_target->IsDead())
    {
        Complete();
        return;
    }

    // Check if we are in range of the resource
    glm::vec2 position = m_owner->GetPosition();
    glm::vec2 targetPosition = m_target->GetPosition();
    float distance = glm::distance(position, targetPosition);

    // If we are too far away, move closer to our target
    if (distance > MIN_ATTACK_DISTANCE)
    {
        auto moveAction = std::make_unique<MoveAction>(m_owner, glm::vec2(0, 0));
        moveAction->SetFollowTarget(m_target);
        moveAction->SetMinimumRange((int)MIN_ATTACK_DISTANCE - 5);
        m_owner->PushAction(std::move(moveAction));

        return;
    }

    // Attacking loop
    if (!m_timer.IsStarted())
    {
        m_timer.Start();
    }
    else if (m_timer.GetTimeInSeconds() >= m_attackSpeedSeconds)
    {
        m_timer.Stop();

        m_owner->GetGame()->GetAudio()->PlaySound("punch_00");
        m_target->Damage();
    }
}

bool AttackAction::IsAttackingPeon()
{
    Peon* peon = dynamic_cast<Peon*>(m_target);
    return (peon != nullptr);
}