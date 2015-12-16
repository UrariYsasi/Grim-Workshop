#include "PCH.hpp"
#include "Entity.hpp"

Entity::Entity(Game* game, Vector2D position) :
    m_game(game),
    m_position(position),
    m_hitbox(SDL_Rect{0, 0, 32, 32})
{
}

Entity::~Entity()
{
}

Vector2D Entity::GetPosition() const
{
    return m_position;
}

void Entity::SetPosition(const Vector2D& position)
{
    m_position = position;
}

SDL_Rect Entity::GetHitbox() const
{
    return m_hitbox;
}

void Entity::SetHitbox(const SDL_Rect& hitbox)
{
    m_hitbox = hitbox;
}