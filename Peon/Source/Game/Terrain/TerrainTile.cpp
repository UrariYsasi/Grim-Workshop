#include "PCH.hpp"
#include "TerrainTile.hpp"
#include "../Game.hpp"
#include "../Entity/Prop.hpp"
#include "../../Engine/Renderer.hpp"
#include "../../Engine/Camera.hpp"

TerrainTile::TerrainTile(Game* game, const glm::vec2& position) :
    m_game(game),
    m_position(position),
    m_rotation(0.0f),
    m_scale(32.0f, 32.0f, 1.0f),
    m_origin(16, 16),
    m_sprite(nullptr)
{
    grim::Texture* texture = game->GetTexture("terrain");
    grim::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::Sprite>(texture, shaderProgram, 0);
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

void TerrainTile::Render()
{
    m_sprite->Render(glm::vec3(m_position, 0.0f), m_rotation, m_scale);
}
