#include "PCH.hpp"
#include "Tree.hpp"
#include "../Game.hpp"

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
    m_game->RenderSprite("tree", 0, 0, m_position.x, m_position.y, 32, 32);
}
