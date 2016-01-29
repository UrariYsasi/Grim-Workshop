#pragma once
#include "Action.hpp"

class Stockpile;

class DumpAction : public Action
{
public:
    DumpAction(Monster* owner);
    virtual ~DumpAction();

    virtual void Update();

private:
    Stockpile* m_target;
};
