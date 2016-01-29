#include "PCH.hpp"
#include "Resource.hpp"

Resource::Resource(Game* game, Vector2D position, Type type) :
    Prop(game, position),
    m_type(type)
{
}

Resource::~Resource()
{
}

Resource::Type Resource::GetType() const
{
    return m_type;
}
