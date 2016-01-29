#include "PCH.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
    m_items.clear();
}

void Inventory::AddItem(const ItemType& type, const int& quantity)
{
    // Tyren Review: Design choice, this creates a LOT of items, why not one object
    // per item type, and have a quantity?
    for (int i = 0; i < quantity; i++)
    {
        std::unique_ptr<Item> item = std::make_unique<Item>(type);
        m_items.push_back(std::move(item));
    }
}

void Inventory::RemoveItem(const ItemType& type, const int& quantity)
{
    for (int i = 0; i < quantity; i++)
    {
        Item* item = nullptr;
        for (auto it = m_items.begin(); it != m_items.end(); it++)
        {
            item = (*it).get();
            if (item != nullptr)
            {
                if (item->GetType() == type)
                {
                    m_items.erase(it++);
                }
            }
        }

        if (item == nullptr)
        {
            return;
        }
    }
}

int Inventory::ItemCount(const ItemType& type)
{
    int count = 0;
    for (auto it = m_items.begin(); it != m_items.end(); it++)
    {
        Item* item = (*it).get();
        if (item->GetType() == type)
        {
            count++;
        }
    }

    return count;
}