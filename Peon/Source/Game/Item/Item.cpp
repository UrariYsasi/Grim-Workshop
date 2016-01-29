#include "PCH.hpp"
#include "Item.hpp"

Item::Item(ItemType type) :
    m_type(type)
{
}

Item::~Item()
{
}

ItemType Item::GetType()
{
    return m_type;
}

void Item::SetType(ItemType type)
{
    m_type = type;
}