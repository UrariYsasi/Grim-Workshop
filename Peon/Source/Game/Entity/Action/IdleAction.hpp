#pragma once
#include "../../../PCH.hpp"
#include "Action.hpp"
#include "../../../Engine/Timer.hpp"

class IdleAction : public Action
{
public:
    IdleAction(Monster* owner);
    virtual ~IdleAction();

    virtual void Update();

private:
    Timer m_timer;
    int m_waitTime; // The time in milliseconds to wait before wandering.
};
