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

// Tyren Review: You never use this, remove it
void MoveAction::SetDestination(const Vector2D& destination)
{
    m_destination = destination;
}

void MoveAction::Update()
{
    Vector2D position = m_owner->GetPosition();

    // Tyren Review: Close, but move it somewhere to the top of the file and make it const?
    int speed = 64;

    if (position != m_destination)
    {
        Vector2D start = position;
        double distance = Vector2D::Distance(start, m_destination);
        Vector2D direction = m_destination - start;
        direction.Normalize();

        position += direction * (speed * m_owner->GetGame()->m_deltaTime);
        if (Vector2D::Distance(start, position) > distance)
        {
            position = m_destination;
            // Tyren Review: Call Complete() instead, in fact make m_isComplete private
            m_isComplete = true;
        }
        
        m_owner->SetPosition(position);
    }
    else
    {
        m_isComplete = true;
    }
}
