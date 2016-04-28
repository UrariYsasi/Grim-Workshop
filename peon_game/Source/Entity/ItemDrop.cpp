#include "PCH.hpp"
#include "ItemDrop.hpp"
#include "../Game.hpp"
#include "../Player.hpp"

ItemDrop::ItemDrop(Game* game, const glm::vec3& position, const ItemType& type) :
    Entity(game, position, EntityID::ITEM_DROP),
    m_type(type)
{
    m_hitBox = grim::graphics::Rect(-16, -16, 32, 32);

    m_sprite = grim::graphics::Sprite(m_game->GetMaterial("sprite_item"), 32, 32, 1);
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
    grim::graphics::Transform transform = m_transform;
    transform.position -= m_origin;
    grim::graphics::RenderCommand command(&m_sprite, transform);
    m_game->GetRenderer()->Submit(command);

    Entity::Render();
}

void ItemDrop::Consume(Obelisk* obelisk)
{
    Entity::Consume(obelisk);

    m_game->GetPlayer()->GetInventory()->GiveItem(m_type);
}