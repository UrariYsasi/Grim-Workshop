#include "PCH.hpp"
#include "Resource.hpp"

Resource::Resource(Game* game, Vector2D position, ItemType type) :
    Prop(game, position),
    m_type(type)
{
}

Resource::~Resource()
{
}

ItemType Resource::GetType() const
{
    return m_type;
}