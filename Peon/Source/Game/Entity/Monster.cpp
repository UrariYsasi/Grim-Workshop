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
    m_actionStack.clear();
}

void Monster::Update()
{
    // Remove any completed actions from the stack
    std::list< std::unique_ptr<Action> >::const_iterator it;
    for (it = m_actionStack.begin(); it != m_actionStack.end(); it++)
    {
        if ((*it)->IsComplete())
        {
            m_actionStack.erase(it++);
        }
    }

    // If this Monster has no actions, add an IdleAction.
    if(m_actionStack.size() == 0)
    {
        SDL_Log("Action stack empty. Adding IdleAction.");
        std::unique_ptr<Action> action = std::make_unique<IdleAction>(this);
        m_actionStack.push_back(std::move(action));
    }


    // Update the current action
    if(m_actionStack.back() != nullptr)
    {
        m_actionStack.back()->Update();

        if(m_actionStack.back()->IsComplete())
        {
            m_actionStack.pop_back();
        }
    }
}

/*
    Push an action onto this Monster's action stack.
*/
void Monster::PushAction(std::unique_ptr<Action> action)
{
    //SDL_Log("%s action pushed.", action->GetName().c_str());
    m_actionStack.push_back(std::move(action));
}

/*
    Clear all this Monster's actions. This is used when commanding them.
*/
void Monster::ClearActions()
{
    //SDL_Log("Clearing action stack...");
    std::list< std::unique_ptr<Action> >::const_iterator it;
    for (it = m_actionStack.begin(); it != m_actionStack.end(); it++)
    {
        (*it)->Complete();
    }
}