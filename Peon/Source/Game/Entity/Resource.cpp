#include "PCH.hpp"
#include "Resource.hpp"
#include "Monster.hpp"

Resource::Resource(Game* game, Vector2D position) :
    Prop(game, position)
{
}

Resource::~Resource()
{
}