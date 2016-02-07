#pragma once
#include "Action.hpp"

class Stockpile;

class DumpAction : public Action
{
public:
    DumpAction(Monster* owner, ItemType dumpItem);
    virtual ~DumpAction();

    virtual void Update(double deltaTime);

private:
    const double MIN_DUMP_DISTANCE = 10.0;

    ItemType m_dumpItem;
    Stockpile* m_target;
};
