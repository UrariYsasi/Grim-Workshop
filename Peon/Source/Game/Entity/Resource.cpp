#include "PCH.hpp"
#include "Resource.hpp"
#include "Monster.hpp"

Resource::Resource(Game* game, Vector2D position, int entityID, ItemType item) :
    Prop(game, position, entityID),
    m_item(item),
    m_health(15),
    m_peonCount(0),
    m_peonLimit(3)
{
}

Resource::~Resource()
{
}

bool Resource::IsFull()
{
    return (m_peonCount >= m_peonLimit);
}

bool Resource::IsDead()
{
    return (m_health <= 0);
}

void Resource::Damage()
{
    m_health--;
}

void Resource::AddPeon()
{
    m_peonCount++;
}

void Resource::RemovePeon()
{
    m_peonCount--;
}