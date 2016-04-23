#include "PCH.hpp"
#include "TerrainTile.hpp"
#include "../Game.hpp"
#include "../World/World.hpp"
#include "../World/Region.hpp"

TerrainTile::TerrainTile(Region* region, const glm::vec2& position) :
    m_region(region),
    m_position(position),
    m_rotation(0.0f),
    m_scale(1.0f),
    m_origin(16.0f, 16.0f),
    m_sprite(nullptr)
{
    Game* game = m_region->GetWorld()->GetGame();
    int variance = static_cast<int>(std::round(grim::utility::Random::Generate(0.0, 5.0)));
    grim::graphics::Texture* texture = game->GetTexture("terrain");
    grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, variance);
}

TerrainTile::~TerrainTile()
{
}

void TerrainTile::SetPosition(const glm::vec2& position)
{
    m_position = position;
}

glm::vec2 TerrainTile::GetPosition() const
{
    return m_position;
}

void TerrainTile::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    if (!m_region->IsExplored())
    {
        m_sprite->color = grim::graphics::Color(0.96f, 0.96f, 0.96f);
    }
    else
    {
        m_sprite->color = grim::graphics::Color(1.0f, 1.0f, 1.0f);
    }

    spriteBatch.AddSprite(glm::vec3(m_position, 0.0f), m_rotation, m_scale, m_sprite.get());
}
