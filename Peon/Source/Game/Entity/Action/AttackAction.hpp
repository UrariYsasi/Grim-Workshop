#pragma once
#include "Action.hpp"

class Entity;

class AttackAction : public Action
{
public:
    AttackAction(Monster* owner, Entity* target);
    virtual ~AttackAction();

    virtual void Update(double deltaTime);
    bool IsAttackingPeon();

private:
    const double MIN_ATTACK_DISTANCE = 20.0;

    Entity* m_target;
    Timer m_timer;
    double m_attackSpeed; // The attack speed, in seconds.
};
