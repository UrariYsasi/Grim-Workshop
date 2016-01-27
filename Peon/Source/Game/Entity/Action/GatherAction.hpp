#pragma once
#include "../../../PCH.hpp"
#include "Action.hpp"
#include "../../../Engine/Timer.hpp"
#include "../Resource.hpp"

class GatherAction : public Action
{
public:
    GatherAction(Monster* owner, Resource* target);
    virtual ~GatherAction();

    virtual void Update();

private:
    Resource* m_target;
    Timer m_timer;
    double m_gatherTime; // The time it takes in milliseconds to gather a resource
    // TODO: base the gather time off of the peons skill level or something
};
