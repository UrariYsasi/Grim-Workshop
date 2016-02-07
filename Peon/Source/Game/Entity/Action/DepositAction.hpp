#pragma once
#include "Action.hpp"

class Stockpile;

class DepositAction : public Action
{
public:
    DepositAction(Monster* owner, ItemType dumpItem);
    virtual ~DepositAction();

    virtual void Update(double deltaTime);

private:
    const double MIN_DUMP_DISTANCE = 10.0;

    ItemType m_dumpItem;
    Stockpile* m_target;
};
