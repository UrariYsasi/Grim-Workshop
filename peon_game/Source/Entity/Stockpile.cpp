#include "PCH.hpp"
#include "Stockpile.hpp"
#include "../Game.hpp"

Stockpile::Stockpile(Game* game, const glm::vec2& position) :
    Prop(game, position, STRUCTURE_STOCKPILE)
{
    m_origin = glm::vec2(0.0f, 0.0f);
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
    spriteBatch.AddSprite(glm::vec3(m_position - m_origin + m_positionOffset, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(32.0f, 32.0f, 0.0f), m_sprite.get());

    Entity::Render(spriteBatch);
}
