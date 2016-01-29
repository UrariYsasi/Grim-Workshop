#pragma once
#include "Prop.hpp"
#include "../Item/Inventory.hpp"

class Stockpile : public Prop
{
public:
    Stockpile(Game* game, Vector2D position);
    virtual ~Stockpile();

    Inventory* GetInventory();

    virtual void Update(double deltaTime);
    virtual void Render();

private:
    Inventory m_inventory;
};
