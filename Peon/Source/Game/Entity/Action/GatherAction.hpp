#pragma once
// Tyren Review: Never include PCH in headers
#include "../../../PCH.hpp"
#include "Action.hpp"

// Tyren Review: Timer is small and changes rarely, move to PCH?
#include "../../../Engine/Timer.hpp"

// Tyren Review: Remove this and forward declare
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
