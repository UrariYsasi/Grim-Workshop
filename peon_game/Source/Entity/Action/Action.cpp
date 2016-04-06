#include "PCH.hpp"
#include "Action.hpp"
#include "../Monster.hpp"

Action::Action(Monster* owner, int actionID, const std::string& name) :
    m_owner(owner),
    m_actionID(actionID),
    m_name(name),
    m_isComplete(false)
{
}

Action::~Action()
{
}

int Action::GetActionID() const
{
    return m_actionID;
}

std::string Action::GetName() const
{
    return m_name;
}

bool Action::IsComplete() const
{
    return m_isComplete;
}

void Action::Complete()
{
    m_isComplete = true;
}