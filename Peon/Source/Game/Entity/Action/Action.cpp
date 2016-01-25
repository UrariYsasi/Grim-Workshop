#include "../../../PCH.hpp"
#include "Action.hpp"
#include "../Monster.hpp"

Action::Action(Monster* owner, const std::string& name) :
    m_owner(owner),
    m_name(name)
{
}

Action::~Action()
{
}

std::string Action::GetName() const
{
    return m_name;
}

void Action::SetName(const std::string& name)
{
    m_name = name;
}
