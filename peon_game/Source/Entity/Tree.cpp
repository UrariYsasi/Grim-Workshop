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

    grim::graphics::Texture* texture = m_game->GetTexture("resource");
    grim::graphics::ShaderProgram* shaderProgram = m_game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::graphics::Sprite>(texture, shaderProgram, 32, 64, 0);
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

void Tree::Render(grim::graphics::SpriteBatch& spriteBatch)
{
    spriteBatch.AddSprite(m_transform.position - m_origin + m_positionOffset, m_transform.rotation, m_transform.scale, m_sprite.get());

    Entity::Render(spriteBatch);
}