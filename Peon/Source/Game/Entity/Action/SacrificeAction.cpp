#include "PCH.hpp"
#include "SacrificeAction.hpp"
#include "../Monster.hpp"
#include "../../Game.hpp"
#include "MoveAction.hpp"
#include "../../Map/Map.hpp"

SacrificeAction::SacrificeAction(Monster* owner) :
    Action(owner, SACRIFICE_ACTION, "Sacrifice")
{
}

SacrificeAction::~SacrificeAction()
{
}

void SacrificeAction::Update(double deltaTime)
{

}
