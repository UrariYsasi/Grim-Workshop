#pragma once
#include "Action.hpp"

class Obelisk;

class DepositAction : public Action
{
public:
    DepositAction(Monster* owner);
    virtual ~DepositAction();

    virtual void Update(float deltaTime);

private:
    const uint32_t MIN_DISTANCE = 96;

    Obelisk* m_obelisk;
};
