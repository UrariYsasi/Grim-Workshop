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
<<<<<<< HEAD
    m_game->RenderSprite("resource", 0, 0, m_position.x, m_position.y, 64, 64);
=======
    // Tyren Review: Constants good, "32" bad
    m_game->RenderSprite("tree", 0, 0, (int)m_position.x, (int)m_position.y, 32, 32);
>>>>>>> b5c1c0b7731553f4a6a51e426f1e3659c27d3b5f
}
