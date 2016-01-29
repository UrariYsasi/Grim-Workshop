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

void Tree::Update()
{
}

void Tree::Render()
{
    m_game->RenderSprite("tree", 0, 0, m_position.GetX(), m_position.GetY(), 32, 32);
}
