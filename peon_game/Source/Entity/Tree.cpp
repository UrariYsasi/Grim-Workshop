#include "PCH.hpp"
#include "Tree.hpp"
#include "../Game.hpp"

Tree::Tree(Game* game, const glm::vec3& position) :
    Resource(game, position, EntityID::RESOURCE_TREE, ItemType::WOOD)
{
    m_origin.y = 32.0f;
    m_hitBox = grim::graphics::Rect(-5, -16, 10, 16);
    m_positionOffset = glm::vec3(grim::utility::Random::Generate(-6.0f, 6.0f), grim::utility::Random::Generate(0.0f, -6.0f), 0.0f);
    m_hp = 1000;

    m_sprite = grim::graphics::Sprite(m_game->GetMaterial("sprite_resource"), 32, 64, 0);
}

Tree::~Tree()
{
}

ItemType Tree::GetItem() const
{
    return m_item;
}

void Tree::Update(float deltaTime)
{
}

void Tree::Render()
{
    grim::graphics::Transform treeTransform = m_transform;
    treeTransform.position -= m_origin;
    grim::graphics::RenderCommand treeCommand(&m_sprite, treeTransform);
    m_game->GetEngine()->GetRenderer()->Submit(treeCommand);

    Entity::Render();
}