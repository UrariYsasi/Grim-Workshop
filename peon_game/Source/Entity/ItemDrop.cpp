#include "PCH.hpp"
#include "ItemDrop.hpp"
#include "../Game.hpp"
#include "../Player.hpp"

ItemDrop::ItemDrop(Game* game, const glm::vec2& position, const ItemType& type) :
    m_type(type),
    Entity(game, position, ENT_ITEM_DROP)
{
    m_origin = glm::vec2(0, 0);
    m_hitBox = grim::graphics::Rect(-16, -16, 32, 32);

    grim::graphics::Texture* texture = game->GetTexture("item");
    grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, 1);
}

ItemDrop::~ItemDrop()
{
}

ItemType ItemDrop::GetItem() const
{
    return m_type;
}

void ItemDrop::Update(float deltaTime)
{
    Entity::Update(deltaTime);
}

void ItemDrop::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    spriteBatch.AddSprite(glm::vec3(m_position - m_origin + m_positionOffset, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), m_sprite.get());

    Entity::Render(spriteBatch);
}

void ItemDrop::Consume(Obelisk* obelisk)
{
    Entity::Consume(obelisk);

    m_game->GetPlayer()->GetInventory()->GiveItem(m_type);
}