#pragma once
#include "Action.hpp"

class Resource;
class Inventory;

class GatherAction : public Action
{
public:
    GatherAction(Monster* owner, Resource* target);
    virtual ~GatherAction();

    virtual void Update(double deltaTime);
    virtual void Complete();
    void Abort();

private:
    const double MIN_GATHER_DISTANCE = 10.0;

    Inventory* m_ownerInventory;
    Resource* m_target;
    Timer m_timer;
    double m_gatherTime; // The time it takes in milliseconds to gather a resource
    // TODO: base the gather time off of the peons skill level or something
};
