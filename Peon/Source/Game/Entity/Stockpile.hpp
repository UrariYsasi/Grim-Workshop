#pragma once

// Tyren Review: Never include PCH in headers
#include "../../PCH.hpp"

#include "Prop.hpp"

// Tyren Review: Try to find a way to forward declare this?
#include "../Item/Inventory.hpp"

class Stockpile : public Prop
{
public:
    Stockpile(Game* game, Vector2D position);
    virtual ~Stockpile();

    Inventory* GetInventory();

    virtual void Update();
    virtual void Render();

private:
    std::unique_ptr<Inventory> m_inventory;
};
