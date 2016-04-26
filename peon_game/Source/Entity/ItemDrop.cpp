#include "PCH.hpp"
#include "ItemDrop.hpp"
#include "../Game.hpp"
#include "../Player.hpp"

ItemDrop::ItemDrop(Game* game, const glm::vec3& position, const ItemType& type) :
    Entity(game, position, EntityID::ITEM_DROP),
    m_type(type)
{
    m_hitBox = grim::graphics::Rect(-16, -16, 32, 32);

    //grim::graphics::Texture* texture = game->GetTexture("item");
    //grim::graphics::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    //m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 32, 1);
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

void ItemDrop::Render()
{
    //spriteBatch.AddSprite(m_transform.position - m_origin + m_positionOffset, m_transform.rotation, m_transform.scale, m_sprite.get());

    Entity::Render();
}

void ItemDrop::Consume(Obelisk* obelisk)
{
    Entity::Consume(obelisk);

    m_game->GetPlayer()->GetInventory()->GiveItem(m_type);
}