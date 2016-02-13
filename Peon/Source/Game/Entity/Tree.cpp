#include "PCH.hpp"
#include "Tree.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Tree::Tree(Game* game, Vector2D position) :
    Resource(game, position, ItemType::WOOD)
{
    m_origin = Vector2D(16, 48);
    m_hitBox = Rectangle(-16, -16, 32, 32);
    m_positionOffset = Vector2D(Random::Generate(-6, 6), Random::Generate(-6, 6));
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
    Entity::Render();

    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("resource", 0, 0, (int)(m_position.x - m_origin.x + m_positionOffset.x), (int)(m_position.y - m_origin.y + m_positionOffset.y), (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y * 2);
}