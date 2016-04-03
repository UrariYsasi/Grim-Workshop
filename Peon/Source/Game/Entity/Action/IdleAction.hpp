#pragma once
#include "Action.hpp"

class IdleAction : public Action
{
public:
    IdleAction(Monster* owner);
    virtual ~IdleAction();

    virtual void Update(float deltaTime);

private:
    grim::utility::Timer m_timer;
    int m_waitTime; // The time in milliseconds to wait before wandering.
};
