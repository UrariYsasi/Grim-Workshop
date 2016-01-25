#pragma once
#include "../../../PCH.hpp"

class Monster;

class Action
{
public:
    Action(Monster* owner, const std::string& name);
    virtual ~Action();

    std::string GetName() const;
    void SetName(const std::string& name);

    virtual void Update() = 0;

private:
    Monster* m_owner;
    std::string m_name;
};
