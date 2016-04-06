#pragma once
#include "Action.hpp"

class Entity;

class PickUpAction : public Action
{
public:
    PickUpAction(Monster* owner, Entity* target);
    virtual ~PickUpAction();

    virtual void Update(float deltaTime);
    virtual void Complete();

private:
    const double MIN_PICK_UP_DISTANCE = 10.0;

    Entity* m_target;
};
