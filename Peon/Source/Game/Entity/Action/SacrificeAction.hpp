/*
    Sacrifice the Entity that the Monster is holding.

    This Action is given to a Peon that is carrying an Entity when the player
    commands them to an Altar.
*/

#pragma once
#include "Action.hpp"

class Altar;

class SacrificeAction : public Action
{
public:
    SacrificeAction(Monster* owner, Altar* altar);
    virtual ~SacrificeAction();

    virtual void Update(double deltaTime);

private:
    const double MIN_DISTANCE = 10.0;

    Altar* m_altar;
};
