#pragma once

class Item;

class Inventory
{
public:
    Inventory();
    ~Inventory();

    void GiveItem(ItemType type, const int& quantity = 1);
    bool RemoveItem(ItemType type, const int& quantity = 1);
    int CountItem(ItemType type);

private:
    std::map<ItemType, int> m_items;
};