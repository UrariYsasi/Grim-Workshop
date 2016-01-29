#include "PCH.hpp"
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

void MoveAction::Update(double deltaTime)
{
    Vector2D position = m_owner->GetPosition();

    if (position != m_destination)
    {
        Vector2D start = position;
        double distance = Vector2D::Distance(start, m_destination);
        Vector2D direction = m_destination - start;
        direction.Normalize();

        position += direction * (MOVE_SPEED * deltaTime);
        if (Vector2D::Distance(start, position) > distance)
        {
            position = m_destination;
            Complete();
        }
        
        m_owner->SetPosition(position);
    }
    else
    {
        Complete();
    }
}
