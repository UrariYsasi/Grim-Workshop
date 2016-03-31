#include "PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"

Stockpile::Stockpile(Game* game, const glm::vec2& position) :
    Prop(game, position, STOCKPILE)
{
    m_origin = glm::vec2(16, 16);
    m_hitBox = grim::graphics::Rect(-16, -16, 32, 32);
}

Stockpile::~Stockpile()
{
}

Inventory* Stockpile::GetInventory()
{
    return &m_inventory;
}

void Stockpile::Update(double deltaTime)
{
}

void Stockpile::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    Entity::Render(spriteBatch);
}
