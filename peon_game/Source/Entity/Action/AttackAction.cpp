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
    glm::vec3 position = m_owner->GetTransform().position;
    glm::vec3 targetPosition = m_target->GetTransform().position;
    float distance = glm::distance(position, targetPosition);

    // If we are too far away, move closer to our target
    if (distance > MIN_ATTACK_DISTANCE)
    {
        auto moveAction = std::make_unique<MoveAction>(m_owner, glm::vec3(0.0f));
        moveAction->SetFollowTarget(m_target);
        moveAction->SetMinimumRange((int)MIN_ATTACK_DISTANCE - 5);
        m_owner->PushAction(std::move(moveAction));

        return;
    }

    // Attack loop
    if (!m_timer.IsStarted())
    {
        m_timer.Start();
    }
    else if (m_timer.GetTimeInSeconds() >= m_attackSpeedSeconds)
    {
        m_timer.Stop();
    
        AttemptAttack();
    }
}

void AttackAction::AttemptAttack()
{
    grim::graphics::Rect targetBounds = m_target->GetHitBox();
    grim::graphics::Rect attackBounds = CalculateAttackBounds();

    //m_owner->GetGame()->GetRenderer()->RenderOutlineRect(attackBounds);

    if (attackBounds.IsCollidingWith(targetBounds))
    {
        m_owner->GetGame()->GetAudio()->PlaySound("punch_00");
        m_target->Damage();
    }
    else
    {
        grim::utility::Debug::Log("Miss!");
    }
}

grim::graphics::Rect AttackAction::CalculateAttackBounds()
{
    grim::graphics::Rect bounds;
    bounds.x = m_owner->GetTransform().position.x + 5.0f;
    bounds.y = m_owner->GetTransform().position.y - 10.0f;
    bounds.width = 5.0f;
    bounds.height = 10.0f;

    return bounds;
}

bool AttackAction::IsAttackingPeon()
{
    Peon* peon = dynamic_cast<Peon*>(m_target);
    return (peon != nullptr);
}