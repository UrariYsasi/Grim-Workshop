#pragma once
#include "../../PCH.hpp"
#include "Item.hpp"

class Inventory
{
public:
    Inventory();
    ~Inventory();

    void AddItem(const int& id, const int& quantity = 1);
    void RemoveItem(const int& id, const int& quantity = 1);
    int ItemCount(const int& id);

private:
    std::list< std::unique_ptr<Item> > m_items;
};