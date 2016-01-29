#include "PCH.hpp"
#include "Entity.hpp"

Entity::Entity(Game* game, Vector2D position) :
    m_game(game),
    m_position(position),
    m_isDeleted(false)
{
}

Entity::~Entity()
{
}

Game* Entity::GetGame()
{
    return m_game;
}

Vector2D Entity::GetPosition() const
{
    return m_position;
}

Vector2D Entity::GetPositionCenter() const
{
    return m_position + Vector2D(16, 16);
}

void Entity::SetPosition(const Vector2D& position)
{
    m_position = position;
}

bool Entity::IsDeleted() const
{
    return m_isDeleted;
}

// Tyren Review: This order does not match the header, please re-order the header or the file
void Entity::Delete()
{
    m_isDeleted = true;
}

/*
    Check if this entity is colliding with the given rectangle.
*/
bool Entity::IsCollidingWithRect(const SDL_Rect& rect) const
{
    SDL_Rect hitbox = { static_cast<int>(m_position.GetX()), static_cast<int>(m_position.GetY()), 32, 32 };

    // Calculate the rectangle bounds
    int leftA = hitbox.x;
    int rightA = hitbox.x + hitbox.w;
    int topA = hitbox.y;
    int bottomA = hitbox.y + hitbox.h;

    int leftB = rect.x;
    int rightB = rect.x + rect.w;
    int topB = rect.y;
    int bottomB = rect.y + rect.h;

    // "Correct" the rectangle
    // This is needed for the mouse selection rectangle
    if (rightA < leftA)
    {
        int temp = leftA;
        leftA = rightA;
        rightA = temp;
    }

    if (rightB < leftB)
    {
        int temp = leftB;
        leftB = rightB;
        rightB = temp;
    }

    if (bottomA < topA)
    {
        int temp = topA;
        topA = bottomA;
        bottomA = temp;
    }

    if (bottomB < topB)
    {
        int temp = topB;
        topB = bottomB;
        bottomB = temp;
    }

    // Check collision
    if (rightA > leftB && leftA < rightB)
    {
        if (bottomA > topB && topA < bottomB)
        {
            return true;
        }
    }

    return false;
}
