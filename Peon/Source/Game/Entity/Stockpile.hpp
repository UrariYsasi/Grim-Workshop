#pragma once
#include "Prop.hpp"
#include "../Item/Inventory.hpp"

class Stockpile : public Prop
{
public:
    Stockpile(Game* game, const glm::vec2& position);
    virtual ~Stockpile();

    Inventory* GetInventory();

    virtual void Update(double deltaTime);
    virtual void Render(grim::SpriteBatch& spriteBatch);

private:
    Inventory m_inventory;
};
