#include "PCH.hpp"
#include "TerrainTile.hpp"
#include "../Game.hpp"
#include "../World/World.hpp"
#include "../World/Region.hpp"

TerrainTile::TerrainTile(Region* region, const glm::vec2& position) :
    m_region(region),
    m_transform(glm::vec3(position.x, position.y, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)),
    m_origin(16.0f, 16.0f),
    m_sprite(m_region->GetWorld()->GetGame()->GetMaterial("sprite_terrain"), 32, 32, 0)
{
    Game* game = m_region->GetWorld()->GetGame();
    uint32_t variance = static_cast<uint32_t>(std::round(grim::utility::Random::Generate(0.0, 5.0)));
    m_sprite.SetFrame(variance);
}

TerrainTile::~TerrainTile()
{
}

void TerrainTile::Render()
{
    /*
    if (!m_region->IsExplored())
    {
        m_sprite->color = grim::graphics::Color(0.96f, 0.96f, 0.96f);
    }
    else
    {
        m_sprite->color = grim::graphics::Color(1.0f, 1.0f, 1.0f);
    }
    */

    grim::graphics::RenderCommand tileCommand(&m_sprite, m_transform);
    m_region->GetWorld()->GetGame()->GetEngine()->GetRenderer()->Submit(tileCommand);
}

grim::graphics::Transform TerrainTile::GetTransform() const
{
    return m_transform;
}