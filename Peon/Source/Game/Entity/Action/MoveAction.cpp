#include "../../../PCH.hpp"
#include "MoveAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"

MoveAction::MoveAction(Monster* owner, const Vector2D& destination) :
    Action(owner, "Move"),
    m_destination(destination)
{
}

MoveAction::~MoveAction()
{
}


Vector2D MoveAction::GetDestination() const
{
    return m_destination;
}

void MoveAction::SetDestination(const Vector2D& destination)
{
    m_destination = destination;
}

void MoveAction::Update()
{
    Vector2D position = m_owner->GetPosition();
    int speed = 64;

    if (position != m_destination)
    {
        Vector2D start = position;
        double distance = Vector2D::Distance(start, m_destination);
        Vector2D direction = Vector2D::Normalize(m_destination - start);

        position += direction * (speed * m_owner->GetGame()->m_deltaTime);
        if (Vector2D::Distance(start, position) > distance)
        {
            position = m_destination;
            m_isComplete = true;
        }

        m_owner->SetPosition(position);
    }
}
