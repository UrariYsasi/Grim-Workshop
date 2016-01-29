#include "../../PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"
#include "../Item/Item.hpp"

Stockpile::Stockpile(Game* game, Vector2D position) :
    Prop(game, position)
{
    // Tyren Review: Same comment as other inventory usage
    m_inventory = std::make_unique<Inventory>();
}

Stockpile::~Stockpile()
{
}

Inventory* Stockpile::GetInventory()
{
    return m_inventory.get();
}

void Stockpile::Update()
{

}

void Stockpile::Render()
{
    m_game->RenderSprite("bonfire_4", 0, 0, m_position.GetX(), m_position.GetY(), 32, 32);

    // Debug stuff
    std::stringstream ss;
    ss << "Wood: " << m_inventory->ItemCount(Item::ID::WOOD);
    m_game->RenderText("dos", m_position.GetX(), m_position.GetY() + 32, ss.str());
    ss.str(" ");

    ss << "Stone: " << m_inventory->ItemCount(Item::ID::STONE);
    m_game->RenderText("dos", m_position.GetX(), m_position.GetY() + 48, ss.str());
    ss.str(" ");
}
