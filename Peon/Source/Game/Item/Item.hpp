#pragma once
// Tyren Review: Never include PCH in headers
#include "../../PCH.hpp"

class Item
{
public:
    // Tyren Review: I love enums, I don't like that you just use it like an int everywhere
    enum ID { NONE, WOOD, STONE };

    Item(const int& id = NONE);
    ~Item();

    int GetID() const;
    void SetID(const int& id);

private:
    int m_id;
};