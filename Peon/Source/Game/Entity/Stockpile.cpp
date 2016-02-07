#include "PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

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
    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("bonfire_4", 0, 0, (int)m_position.x, (int)m_position.y, (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y);

    // Debug stuff
    std::stringstream ss;
    ss << "Wood: " << m_inventory.CountItem(ItemType::WOOD);
    renderer->RenderText("dos", (int)m_position.x, (int)m_position.y + 32, ss.str());
    ss.str(" ");

    ss << "Stone: " << m_inventory.CountItem(ItemType::STONE);
    renderer->RenderText("dos", (int)m_position.x, (int)m_position.y + 48, ss.str());
    ss.str(" ");

    ss << "Coal: " << m_inventory.CountItem(ItemType::COAL);
    renderer->RenderText("dos", (int)m_position.x, (int)m_position.y + 64, ss.str());
    ss.str(" ");

    ss << "Iron Ore: " << m_inventory.CountItem(ItemType::IRON_ORE);
    renderer->RenderText("dos", (int)m_position.x, (int)m_position.y + 80, ss.str());
    ss.str(" ");

    ss << "Iron Bar: " << m_inventory.CountItem(ItemType::IRON_BAR);
    renderer->RenderText("dos", (int)m_position.x, (int)m_position.y + 96, ss.str());
    ss.str(" ");
}
