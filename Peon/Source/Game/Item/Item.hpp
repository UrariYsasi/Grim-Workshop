#pragma once

class Item
{
public:
    Item(ItemType type = ItemType::NONE);
    ~Item();

    ItemType GetType();
    void SetType(ItemType type);

private:
    ItemType m_type;
};