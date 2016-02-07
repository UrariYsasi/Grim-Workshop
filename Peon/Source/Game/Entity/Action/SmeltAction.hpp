#pragma once
#include "Action.hpp"

class Resource;
class Forge;

class SmeltAction : public Action
{
public:
    SmeltAction(Monster* owner, Forge* forge);
    virtual ~SmeltAction();

    virtual void Update(double deltaTime);

private:
    const double MIN_DISTANCE = 10.0;

    Forge* m_forge;
    Timer m_timer;
    double m_forgeTime;
};
