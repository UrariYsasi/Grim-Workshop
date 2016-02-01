#include "PCH.hpp"
#include "Rock.hpp"
#include "../Game.hpp"

Rock::Rock(Game* game, Vector2D position) :
    Resource(game, position, NONE)
{
}

Rock::~Rock()
{
}

void Rock::Update(double deltaTime)
{
}

void Rock::Render()
{
    m_game->RenderSprite("resource", 2, 0, m_position.x, m_position.y, 32, 32);
}
