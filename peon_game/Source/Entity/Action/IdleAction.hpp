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
    float m_waitTimeSeconds; // The time, in seconds, to wait before wandering.
};
