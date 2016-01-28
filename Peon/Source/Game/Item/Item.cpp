#include "../../PCH.hpp"
#include "Item.hpp"

Item::Item(const int& id) :
    m_id(id)
{
}

Item::~Item()
{
}

int Item::GetID() const
{
    return m_id;
}

void Item::SetID(const int& id)
{
    m_id = id;
}