#include "PCH.hpp"
#include "Tile.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"
#include "../../Engine/Camera.hpp"

Tile::Tile(Game* game, const Vector2D& position, const int& spriteColumn, const int& spriteRow) :
    m_game(game),
    m_origin(16, 16),
    m_position(position),
    m_spritesheet("terrain"),
    m_spriteColumn(spriteColumn),
    m_spriteRow(spriteRow)
{
}

Tile::~Tile()
{
}

void Tile::SetPosition(const Vector2D& position)
{
    m_position = position;
}

Vector2D Tile::GetPosition() const
{
    return m_position;
}

void Tile::Render()
{
    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite(m_spritesheet, m_spriteColumn, m_spriteRow, (int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), TILE_SIZE, TILE_SIZE);

    if (Debug::IsFlagEnabled(RENDER_TILE_OUTLINES))
    {
        Rectangle outline((int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), TILE_SIZE, TILE_SIZE);
        renderer->RenderOutlineRect(outline, SDL_Color{ 0, 0, 0, 15 });
    }
}