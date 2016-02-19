#include "PCH.hpp"
#include "Rock.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Rock::Rock(Game* game, Vector2D position) :
    Resource(game, position, ROCK, ItemType::STONE)
{
    m_origin = Vector2D(16, 16);
}

Rock::~Rock()
{
}

ItemType Rock::GetItem() const
{
    int rand = (int)Random::Generate(0.0, 100.0);
    if (rand > 95)
    {
        return ItemType::IRON_ORE;
    }
    else if (rand > 80)
    {
        return ItemType::COAL;
    }

    return m_item;
}

void Rock::Update(double deltaTime)
{
}

void Rock::Render()
{
    Renderer* renderer = m_game->GetRenderer();
    renderer->RenderSprite("resource", 2, 0, (int)m_position.x, (int)m_position.y, (int)SPRITE_SIZE.x, (int)SPRITE_SIZE.y);

    Entity::Render();
}