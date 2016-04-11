#include "PCH.hpp"
#include "AttackAction.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../Monster.hpp"
#include "../Peon.hpp"

AttackAction::AttackAction(Monster* owner, Entity* target) :
    Action(owner, ATTACK_ACTION, "Attack"),
    m_target(target),
    m_attackSpeed(2)
{
    m_attackSpeed = grim::utility::Random::Generate(0.5, 2.0);
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
    glm::vec2 targetPosition = m_target->GetPosition();
    glm::vec2 monsterPosition = m_owner->GetPosition();
    double distance = glm::distance(monsterPosition, targetPosition);

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
    else if (m_timer.GetTimeInMilliseconds() > (m_attackSpeed * 1000))
    {
        m_timer.Stop();

        m_owner->GetGame()->GetAudio()->PlaySound("punch_00");
        m_target->Damage();
        m_owner->GetGame()->GetAudio()->PlaySound("damage");
    }
}

bool AttackAction::IsAttackingPeon()
{
    Peon* peon = dynamic_cast<Peon*>(m_target);
    return (peon != nullptr);
}