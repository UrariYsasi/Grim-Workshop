#include "PCH.hpp"
#include "PickUpAction.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../Monster.hpp"

PickUpAction::PickUpAction(Monster* owner, Entity* target) :
    Action(owner, PICK_UP_ACTION, "Pick Up"),
    m_target(target)
{
}

PickUpAction::~PickUpAction()
{
}

void PickUpAction::Update(float deltaTime)
{
    if (m_target->IsHeld())
    {
        Complete();
        return;
    }

    // Check if we are in range of the target
    glm::vec2 targetPosition = m_target->GetPosition();
    glm::vec2 monsterPosition = m_owner->GetPosition();
    double distance = glm::distance(monsterPosition, targetPosition);

    if (distance <= MIN_PICK_UP_DISTANCE)
    {
        m_owner->DropHeldEntity();
        m_owner->SetHeldEntity(m_target);
        Complete();
    }
    else
    {
        // We aren't close enough.
        m_owner->PushAction(std::make_unique<MoveAction>(m_owner, m_target->GetPosition()));
    }
}

void PickUpAction::Complete()
{
    Action::Complete();
}