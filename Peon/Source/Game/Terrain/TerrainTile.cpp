#include "PCH.hpp"
#include "TerrainTile.hpp"
#include "../Game.hpp"
#include "../Entity/Prop.hpp"
#include "../../Engine/Renderer.hpp"
#include "../../Engine/Camera.hpp"

TerrainTile::TerrainTile(Game* game, const Vector2D& position) :
    m_game(game),
    m_position(position),
    m_origin(16, 16),
    m_spritesheet("terrain"),
    m_spriteColumn(0),
    m_spriteRow(0)
{
}

TerrainTile::~TerrainTile()
{
}

void TerrainTile::SetPosition(const Vector2D& position)
{
    m_position = position;
}

Vector2D TerrainTile::GetPosition() const
{
    return m_position;
}

void TerrainTile::Render()
{
    grim::Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite(m_spritesheet, m_spriteColumn, m_spriteRow, (int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), 32, 32);

    if (Debug::IsFlagEnabled(RENDER_TILE_OUTLINES))
    {
        Rect outline((int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), 32, 32);
        renderer->RenderOutlineRect(outline, SDL_Color{ 0, 0, 0, 15 });
    }
}
