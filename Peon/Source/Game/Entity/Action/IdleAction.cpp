#include "../../../PCH.hpp"
#include "IdleAction.hpp"

IdleAction::IdleAction(Monster* owner) :
    Action(owner, "Idle")
{
}

IdleAction::~IdleAction()
{
}

void IdleAction::Update()
{
}
