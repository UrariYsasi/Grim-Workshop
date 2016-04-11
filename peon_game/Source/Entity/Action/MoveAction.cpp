#include "PCH.hpp"
#include "MoveAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "../../World/World.hpp"

MoveAction::MoveAction(Monster* owner, const glm::vec2& destination) :
    Action(owner, MOVE_ACTION, "Move"),
    m_destination(destination),
    m_followTarget(nullptr),
    m_range(1),
    m_hopOffset(0),
    m_hopIndex(0),
    m_hopAmp(6),
    m_hopFreq(15)
{
    m_hopFreq += grim::utility::Random::Generate(-3.0, 3.0);
}

MoveAction::~MoveAction()
{
    m_owner->SetPositionOffset(glm::vec2(0, 0));
}


glm::vec2 MoveAction::GetDestination() const
{
    return m_destination;
}

void MoveAction::Update(float deltaTime)
{
    // If we have a follow target, update our destination.
    if (m_followTarget != nullptr)
    {
        m_destination = m_followTarget->GetPosition();
    }

    m_hopIndex += deltaTime;
    m_hopOffset = std::abs(std::sin(m_hopIndex * m_hopFreq) * m_hopAmp);
    m_owner->SetPositionOffset(glm::vec2(0, -m_hopOffset));

    glm::vec2 position = m_owner->GetPosition();
    glm::vec2 start = position;
    glm::vec2 direction = m_destination - start;
    direction = glm::normalize(direction);

    glm::vec2 velocity = direction * (float)(m_owner->GetMoveSpeed() * deltaTime);

    // Check for collisions
    bool xCollision = false;
    bool yCollision = false;
    /*
    World* map = m_owner->GetGame()->GetWorld();
    std::list<Entity*> ents = map->FindEntitiesInRange(NONE, position + velocity, 64);
    for (auto it = ents.begin(); it != ents.end(); it++)
    {
        if ((*it) != m_owner && !(*it)->IsDead())
        {
            Rect hitBox = (*it)->GetHitBox();
            if (hitBox.ContainsPoint(position + Vector2D(velocity.x, 0)))
            {
                xCollision = true;
            }

            if (hitBox.ContainsPoint(position + Vector2D(0, velocity.y)))
            {
                yCollision = true;
            }
        }
    }
    */

    if (!xCollision)
    {
        position.x += velocity.x;
    }

    if (!yCollision)
    {
        position.y += velocity.y;
    }

    if (direction.x > 0)
    {
        m_owner->SetDirection(Entity::Direction::RIGHT);
    }
    else if (direction.x < 0)
    {
        m_owner->SetDirection(Entity::Direction::LEFT);
    }

    if (glm::distance(position, m_destination) <= m_range)
    {
        Complete();
    }

    m_owner->SetPosition(position);
}

void MoveAction::SetFollowTarget(Entity* target)
{
    m_followTarget = target;
}

void MoveAction::SetMinimumRange(int range)
{
    m_range = range;
}