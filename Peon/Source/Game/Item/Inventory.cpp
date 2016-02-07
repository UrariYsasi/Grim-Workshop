#include "PCH.hpp"
#include "Inventory.hpp"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
    m_items.clear();
}

void Inventory::GiveItem(ItemType type, const int& quantity)
{
    m_items[type] += quantity;
}

bool Inventory::RemoveItem(ItemType type, const int& quantity)
{
    if (m_items[type] < quantity)
    {
        return false;
    }

    m_items[type] -= quantity;
    return true;
}

int Inventory::CountItem(ItemType type)
{
    return m_items[type];
}