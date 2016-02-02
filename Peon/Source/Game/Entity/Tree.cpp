#include "PCH.hpp"
#include "Tree.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Tree::Tree(Game* game, Vector2D position) :
    Resource(game, position, NONE)
{
}

Tree::~Tree()
{
}

void Tree::Update(double deltaTime)
{
}

void Tree::Render()
{
    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("resource", 0, 0, (int)m_position.x, (int)m_position.y, (int)SPRITE_SIZE.x * 2, (int)SPRITE_SIZE.y * 2);
}
