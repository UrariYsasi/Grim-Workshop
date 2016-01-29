#pragma once
// Tyren Review: Never include PCH in headers
#include "../../../PCH.hpp"

#include "Action.hpp"

// Tyren Review: Just include in PCH?
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
