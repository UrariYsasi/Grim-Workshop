#include "PCH.hpp"
#include "Forge.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Forge::Forge(Game* game, const glm::vec2& position) :
    Prop(game, position, NONE)
{
}

Forge::~Forge()
{
}

void Forge::Update(double deltaTime)
{
}

void Forge::Render()
{
    grim::Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("structure", 0, 0, (int)m_position.x, (int)m_position.y, (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y);

    Entity::Render();
}