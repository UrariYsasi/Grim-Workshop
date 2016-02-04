#pragma once
#include "Action.hpp"

class Stockpile;

class DumpAction : public Action
{
public:
    DumpAction(Monster* owner, const ItemType& dumpType);
    virtual ~DumpAction();

    virtual void Update(double deltaTime);

private:
    const double MIN_DUMP_DISTANCE = 10.0;

    Stockpile* m_target;
    ItemType m_dumpType;
};
