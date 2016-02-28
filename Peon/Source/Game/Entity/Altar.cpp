#include "PCH.hpp"
#include "Altar.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Altar::Altar(Game* game, Vector2D position) :
    Prop(game, position, ALTAR)
{
    m_origin = Vector2D(16, 16);
    m_hitBox = Rect(-16, -16, 32, 32);
}

Altar::~Altar()
{
}

void Altar::Update(double deltaTime)
{
}

void Altar::Render()
{
    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("structure", 1, 0, (int)(m_position.x - m_origin.x), (int)(m_position.y - m_origin.y), (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y);

    Entity::Render();
}
