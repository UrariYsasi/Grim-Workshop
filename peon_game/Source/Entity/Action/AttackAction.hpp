#pragma once
#include "Action.hpp"

class Entity;

class AttackAction : public Action
{
public:
    AttackAction(Monster* owner, Entity* target);
    virtual ~AttackAction();

    virtual void Update(float deltaTime);
    bool IsAttackingPeon();

public:
    const float MIN_ATTACK_DISTANCE = 20.0f;

private:
    Entity* m_target;
    grim::utility::Timer m_timer;
    double m_attackSpeedSeconds; // The attack speed, in seconds.
};
