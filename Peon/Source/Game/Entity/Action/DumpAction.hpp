#pragma once
// Tyren Review: Never include PCH in headers
#include "../../../PCH.hpp"

#include "Action.hpp"

// Tyren Review: Forward decalre
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
