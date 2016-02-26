#include "PCH.hpp"
#include "AttackAction.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../Monster.hpp"
#include "../Peon.hpp"

AttackAction::AttackAction(Monster* owner, Entity* target) :
    Action(owner, ATTACK_ACTION, "Attack"),
    m_target(target)
{
}

AttackAction::~AttackAction()
{
}

void AttackAction::Update(double deltaTime)
{
    if (m_target->IsDead())
    {
        Complete();
        return;
    }

    // Check if we are in range of the resource
    Vector2D targetPosition = m_target->GetPosition();
    Vector2D monsterPosition = m_owner->GetPosition();
    double distance = Vector2D::Distance(monsterPosition, targetPosition);

    // If we are too far away, move closer to our target
    if (distance > MIN_ATTACK_DISTANCE)
    {
        auto moveAction = std::make_unique<MoveAction>(m_owner);
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
    else if (m_timer.GetTime() > ATTACK_SPEED)
    {
        m_timer.Stop();

        m_owner->GetGame()->PlaySound("sword");
        m_target->Damage();
    }
}

bool AttackAction::IsAttackingPeon()
{
    Peon* peon = dynamic_cast<Peon*>(m_target);
    return (peon != nullptr);
}