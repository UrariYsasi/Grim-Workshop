#include "PCH.hpp"
#include "Tree.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Tree::Tree(Game* game, const glm::vec2& position) :
    Resource(game, position, TREE, ItemType::WOOD)
{
    m_origin = glm::vec2(0, 16);
    m_hitBox = Rect(-16, -16, 32, 32);
    m_positionOffset = glm::vec2(Random::Generate(-6, 6), Random::Generate(0, -6));
    m_hp = 10;

    grim::Texture* texture = game->GetTexture("resource");
    grim::ShaderProgram* shaderProgram = game->GetShaderProgram("basic_shader");
    m_sprite = std::make_unique<grim::Sprite>(texture, shaderProgram, 32, 64, 0);
}

Tree::~Tree()
{
}

ItemType Tree::GetItem() const
{
    return m_item;
}

void Tree::Update(double deltaTime)
{
}

void Tree::Render()
{
    m_sprite->Render(glm::vec3(m_position - m_origin + m_positionOffset, 0.0f), glm::vec3(0), glm::vec3(32, 64, 0));

    Entity::Render();
}