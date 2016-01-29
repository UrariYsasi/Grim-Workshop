#include "PCH.hpp"
#include "Action.hpp"
#include "../Monster.hpp"

Action::Action(Monster* owner, const std::string& name) :
    m_owner(owner),
    m_name(name),
    m_isComplete(false)
{
}

Action::~Action()
{
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
