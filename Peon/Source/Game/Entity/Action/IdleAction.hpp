#pragma once
#include "../../../PCH.hpp"
#include "Action.hpp"

class IdleAction : public Action
{
public:
    IdleAction(Monster* owner);
    virtual ~IdleAction();
};
