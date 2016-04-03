#pragma once
#include "Action.hpp"

class Resource;
class Forge;

class SmeltAction : public Action
{
public:
    SmeltAction(Monster* owner, Forge* forge);
    virtual ~SmeltAction();

    virtual void Update(float deltaTime);

private:
    const double MIN_DISTANCE = 10.0;

    Forge* m_forge;
    grim::utility::Timer m_timer;
    double m_forgeTime;
};
