#include "PCH.hpp"
#include "Tree.hpp"
#include "Game.hpp"

Tree::Tree(Game* game, const Vector2D& position) :
    Entity(game, position)
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
    m_game->RenderTexture("tree", m_position.GetX(), m_position.GetY(), 32, 32);
}