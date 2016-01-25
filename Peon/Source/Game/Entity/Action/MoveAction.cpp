#include "../../../PCH.hpp"
#include "MoveAction.hpp"

MoveAction::MoveAction(Monster* owner) :
    Action(owner, "Move")
{
}

MoveAction::~MoveAction()
{
}

void MoveAction::Update()
{
}
