#pragma once
#include "Prop.hpp"
#include "../Item/Inventory.hpp"

class Stockpile : public Prop
{
public:
    Stockpile(Game* game, const glm::vec2& position);
    virtual ~Stockpile();

    Inventory* GetInventory();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);

private:
    Inventory m_inventory;
};