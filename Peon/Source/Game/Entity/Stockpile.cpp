#include "PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"
#include "../Item/Item.hpp"

Stockpile::Stockpile(Game* game, Vector2D position) :
    Prop(game, position)
{
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

void Stockpile::Render()
{
    // Tyren Review: Constants good
    m_game->RenderSprite("bonfire_4", 0, 0, (int)m_position.x, (int)m_position.y, 32, 32);

    // Debug stuff
    std::stringstream ss;
    ss << "Wood: " << m_inventory.ItemCount(ItemType::WOOD);
    m_game->RenderText("dos", (int)m_position.x, (int)m_position.y + 32, ss.str());
    ss.str(" ");

    ss << "Stone: " << m_inventory.ItemCount(ItemType::STONE);
    m_game->RenderText("dos", (int)m_position.x, (int)m_position.y + 48, ss.str());
    ss.str(" ");
}
