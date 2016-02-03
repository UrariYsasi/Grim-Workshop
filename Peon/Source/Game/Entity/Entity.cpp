#include "PCH.hpp"
#include "Entity.hpp"

Entity::Entity(Game* game, Vector2D position) :
    m_game(game),
    m_position(position),
    m_isDeleted(false),
    SPRITE_SIZE(Vector2D(32, 32))
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

/*
    Mark this Entity for deletion. It will be deleted at the end of the frame.
*/
void Entity::Delete()
{
    m_isDeleted = true;
}

/*
    Check if this entity is colliding with the given rectangle.
*/
bool Entity::IsCollidingWithRect(const Rectangle& rect) const
{
    // TODO
    // Actual hitboxes
    Rectangle hitbox(m_position.x, m_position.y, 32, 32);

    // Calculate the rectangle bounds
    double leftA = hitbox.x;
    double rightA = hitbox.x + hitbox.width;
    double topA = hitbox.y;
    double bottomA = hitbox.y + hitbox.height;

    double leftB = rect.x;
    double rightB = rect.x + rect.width;
    double topB = rect.y;
    double bottomB = rect.y + rect.height;

    // "Correct" the rectangle
    // This is needed for the mouse selection rectangle
    if (rightA < leftA)
    {
        double temp = leftA;
        leftA = rightA;
        rightA = temp;
    }

    if (rightB < leftB)
    {
        double temp = leftB;
        leftB = rightB;
        rightB = temp;
    }

    if (bottomA < topA)
    {
        double temp = topA;
        topA = bottomA;
        bottomA = temp;
    }

    if (bottomB < topB)
    {
        double temp = topB;
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
