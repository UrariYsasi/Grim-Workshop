#include "../../PCH.hpp"
#include "Monster.hpp"
#include "../Game.hpp"

Monster::Monster(Game* game, Vector2D position) :
    Entity(game, position)
{
}

Monster::~Monster()
{
    // Free the action stack
    while(!m_actionStack.empty())
    {
        m_actionStack.pop();
    }
}

void Monster::Update()
{
    // If this Monster has no actions, add an IdleAction.
    if(m_actionStack.size() == 0)
    {
        std::unique_ptr<Action> action = std::make_unique<IdleAction>(this);
        m_actionStack.push(std::move(action));
    }


    // Update the current action
    if(m_actionStack.top() != nullptr)
    {
        m_actionStack.top()->Update();

        if(m_actionStack.top()->IsComplete())
        {
            m_actionStack.pop();
        }
    }
}

/*
    Push an action onto this Monster's action stack.
*/
void Monster::PushAction(std::unique_ptr<Action> action)
{
    m_actionStack.push(std::move(action));
}
