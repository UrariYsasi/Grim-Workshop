#pragma once
#include "Action.hpp"

class Stockpile;

class DepositAction : public Action
{
public:
    DepositAction(Monster* owner, ItemType dumpItem, const int& quantity = 1);
    virtual ~DepositAction();

    virtual void Update(float deltaTime);

private:
    const double MIN_DISTANCE = 10.0;

    int m_quantity;
    ItemType m_dumpItem;
    Stockpile* m_target;
};
