#include "PCH.hpp"
#include "Resource.hpp"
#include "Monster.hpp"

Resource::Resource(Game* game, const glm::vec2& position, EntityID ID, ItemType item) :
    Entity(game, position, ID),
    m_item(item),
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

void Resource::AddPeon()
{
    m_peonCount++;
}

void Resource::RemovePeon()
{
    m_peonCount--;
}