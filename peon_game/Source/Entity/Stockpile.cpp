#include "PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"

Stockpile::Stockpile(Game* game, const glm::vec3& position) :
    Entity(game, position, EntityID::STRUCTURE_STOCKPILE)
{
    m_hitBox = grim::graphics::Rect(-16.0f, -16.0f, 32.0f, 32.0f);

    grim::graphics::Texture* texture = game->GetTexture("structure");
    grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, 8);
}

Stockpile::~Stockpile()
{
}

Inventory* Stockpile::GetInventory()
{
    return &m_inventory;
}

void Stockpile::Update(float deltaTime)
{
}

void Stockpile::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    spriteBatch.AddSprite(m_transform.position - m_origin + m_positionOffset, m_transform.rotation, m_transform.scale, m_sprite.get());

    Entity::Render(spriteBatch);
}
