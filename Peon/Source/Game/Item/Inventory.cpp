#include "../../PCH.hpp"
#include "Inventory.hpp"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
    m_items.clear();
}

void Inventory::AddItem(const int& id, const int& quantity)
{
    for (int i = 0; i < quantity; i++)
    {
        std::unique_ptr<Item> item = std::make_unique<Item>(id);
        m_items.push_back(std::move(item));
    }
}

void Inventory::RemoveItem(const int& id, const int& quantity)
{
    for (int i = 0; i < quantity; i++)
    {
        Item* item = nullptr;
        for (auto it = m_items.begin(); it != m_items.end(); it++)
        {
            item = (*it).get();
            if (item != nullptr)
            {
                if (item->GetID() == id)
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

int Inventory::ItemCount(const int& id)
{
    int count = 0;
    for (auto it = m_items.begin(); it != m_items.end(); it++)
    {
        Item* item = (*it).get();
        if (item->GetID() == id)
        {
            count++;
        }
    }

    return count;
}