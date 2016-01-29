#pragma once

class Item;

class Inventory
{
public:
    Inventory();
    ~Inventory();

    void AddItem(const ItemType& type, const int& quantity = 1);
    void RemoveItem(const ItemType& type, const int& quantity = 1);
    int ItemCount(const ItemType& type);

private:
    std::list< std::unique_ptr<Item> > m_items;
};