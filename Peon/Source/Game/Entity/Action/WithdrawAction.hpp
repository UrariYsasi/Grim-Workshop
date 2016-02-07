#pragma once
#include "Action.hpp"

class Stockpile;

class WithdrawAction : public Action
{
public:
    WithdrawAction(Monster* owner, ItemType withdrawItem, const int& quantity = 1);
    virtual ~WithdrawAction();

    virtual void Update(double deltaTime);

private:
    const double MIN_DISTANCE = 10.0;

    int m_quantity;
    ItemType m_withdrawItem;
    Stockpile* m_target;
};
