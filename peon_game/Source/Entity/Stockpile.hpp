#pragma once
#include "Entity.hpp"
#include "../Item/Inventory.hpp"

class Stockpile : public Entity
{
public:
    Stockpile(Game* game, const glm::vec3& position);
    virtual ~Stockpile();

    Inventory* GetInventory();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);

private:
    Inventory m_inventory;
};
