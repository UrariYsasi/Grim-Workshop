#include "PCH.hpp"
#include "Resource.hpp"
#include "Monster.hpp"

Resource::Resource(Game* game, Vector2D position, ItemType item) :
    Prop(game, position),
    m_item(item)
{
}

Resource::~Resource()
{
}