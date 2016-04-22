#include "PCH.hpp"
#include "Tree.hpp"
#include "../Game.hpp"

Tree::Tree(Game* game, const glm::vec2& position) :
    Resource(game, position, ENT_TREE, ItemType::WOOD)
{
    m_origin = glm::vec2(0, 16);
    m_hitBox = grim::graphics::Rect(-16, -16, 32, 32);
    m_positionOffset = glm::vec2(grim::utility::Random::Generate(-6.0, 6.0), grim::utility::Random::Generate(0.0, -6.0));
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
    spriteBatch.AddSprite(glm::vec3(m_position - m_origin + m_positionOffset, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), m_sprite.get());

    Entity::Render(spriteBatch);
}