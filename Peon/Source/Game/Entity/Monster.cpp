#include "../../PCH.hpp"
#include "Monster.hpp"
#include "../Game.hpp"

Monster::Monster(Game* game, Vector2D position) :
    Entity(game, position),
    m_state(IDLE),
    m_destination(0, 0),
    m_moveSpeed(64)
{
    m_stateHandler[NONE] = nullptr;
    m_stateHandler[IDLE] = nullptr;
    m_stateHandler[WALKING] = &Monster::WalkingState;
    m_stateHandler[WORKING] = nullptr;
}

Monster::~Monster()
{
    // Free the action stack
    while(!m_actionStack.empty())
    {
        m_actionStack.pop();
    }
}

Vector2D Monster::GetDestination() const
{
    return m_destination;
}

void Monster::SetDestination(const Vector2D& destination)
{
    m_destination = destination;
}

void Monster::Update()
{
    if(m_actionStack.size() != 0)
    {
        // Update the current action
        m_actionStack.top()->Update();
    }
    else
    {
        // This monster has no actions, so add an idle action.
        std::unique_ptr<Action> action = std::make_unique<IdleAction>(this);
        m_actionStack.push(std::move(action));
    }

    stateFunction stateFunc = m_stateHandler[m_state];
    if (stateFunc != nullptr)
    {
       (this->*stateFunc)();
    }
}

/*
    Make this Monster start navigating to the given destination.
*/
void Monster::StartNavigation(const Vector2D& destination)
{
    m_destination = destination;
    m_state = WALKING;
}

/*
    Push an action onto this Monster's action stack.
*/
void Monster::PushAction(std::unique_ptr<Action> action)
{
    m_actionStack.push(std::move(action));
}

/*
    The Monster's WALKING state.
*/
void Monster::WalkingState()
{
    if (m_position != m_destination)
    {
        Vector2D start = m_position;
        double distance = Vector2D::Distance(start, m_destination);
        Vector2D direction = Vector2D::Normalize(m_destination - start);

        m_position += direction * (m_moveSpeed * m_game->m_deltaTime);
        if (Vector2D::Distance(start, m_position) > distance)
        {
            m_position = m_destination;
            m_state = IDLE;
            m_actionStack.pop();
        }
    }
}
