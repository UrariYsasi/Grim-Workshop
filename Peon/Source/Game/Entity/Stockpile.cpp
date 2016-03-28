#include "PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Stockpile::Stockpile(Game* game, const glm::vec2& position) :
    Prop(game, position, STOCKPILE)
{
    m_origin = glm::vec2(16, 16);
    m_hitBox = grim::Rect(-16, -16, 32, 32);
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

void Stockpile::Render(grim::SpriteBatch& spriteBatch)
{
    grim::Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("structure", 0, 1, (int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y);

    Entity::Render(spriteBatch);
}
