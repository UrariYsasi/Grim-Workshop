#include "PCH.hpp"
#include "Rock.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

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
    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("resource", 2, 0, (int)m_position.x, (int)m_position.y, (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y);
}
