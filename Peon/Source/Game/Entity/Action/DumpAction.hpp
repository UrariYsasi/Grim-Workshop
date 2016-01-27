#pragma once
#include "../../../PCH.hpp"
#include "Action.hpp"
#include "../Stockpile.hpp"

class DumpAction : public Action
{
public:
    DumpAction(Monster* owner);
    virtual ~DumpAction();

    virtual void Update();

private:
    Stockpile* m_target;
};
