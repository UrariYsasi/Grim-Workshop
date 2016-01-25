#pragma once
#include "../../../PCH.hpp"
#include "Action.hpp"

class MoveAction : public Action
{
public:
    MoveAction(Monster* owner);
    virtual ~MoveAction();

    virtual void Update();
};
