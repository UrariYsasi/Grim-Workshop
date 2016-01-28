#pragma once
#include "../../PCH.hpp"

class Item
{
public:
    enum ID { NONE, WOOD, STONE };

    Item(const int& id = NONE);
    ~Item();

    int GetID() const;
    void SetID(const int& id);

private:
    int m_id;
};