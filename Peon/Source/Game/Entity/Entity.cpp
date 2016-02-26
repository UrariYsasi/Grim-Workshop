#include "PCH.hpp"
#include "Entity.hpp"
#include "../Game.hpp"
#include "../../Engine/Renderer.hpp"

Entity::Entity(Game* game, const Vector2D& position, int entityID) :
    SPRITE_SIZE(32, 32),
    m_game(game),
    m_entityID(entityID),
    m_position(position),
    m_origin(0, 0),
    m_positionOffset(0, 0),
    m_isDeleted(false),
    m_hitBox(-16, -16, 16, 16),
    m_selectionHitBox(-16, -16, 16, 16),
    m_hp(3),
    m_isHeld(false)
{
}

Entity::~Entity()
{
}

Game* Entity::GetGame()
{
    return m_game;
}

int Entity::GetEntityID()
{
    return m_entityID;
}

Vector2D Entity::GetPosition() const
{
    return m_position;
}

Vector2D Entity::GetOrigin() const
{
    return m_origin;
}

Vector2D Entity::GetPositionOffset() const
{
    return m_positionOffset;
}

void Entity::SetPosition(const Vector2D& position)
{
    m_position = position;
}

void Entity::SetPositionOffset(const Vector2D& positionOffset)
{
    m_positionOffset = positionOffset;
}

bool Entity::IsDeleted() const
{
    return m_isDeleted;
}

Rectangle Entity::GetHitBox() const
{
    return Rectangle(m_position.x + m_hitBox.x, m_position.y + m_hitBox.y, m_hitBox.width, m_hitBox.height);
}

void Entity::Render()
{
    if (Debug::IsFlagEnabled(RENDER_HITBOXES))
    {
        Rectangle hitBox = GetHitBox();
        m_game->GetRenderer()->RenderOutlineRect(hitBox, SDL_Color{ 255, 0, 0, 255 });
    }

    if (Debug::IsFlagEnabled(RENDER_ORIGINS))
    {
        Rectangle originRect((int)m_position.x - 1, (int)m_position.y - 1, 3, 3);
        m_game->GetRenderer()->RenderFillRect(originRect, SDL_Color{ 255, 0, 0, 255 });
    }

    /*
    if (m_hp < 5)
    {
        m_game->GetRenderer()->RenderText("dos", (int)m_position.x, (int)m_position.y, std::to_string(m_hp));
    }
    */
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
    Rectangle hitBox = GetHitBox();

    // Calculate the rectangle bounds
    double leftA = hitBox.x;
    double rightA = hitBox.x + hitBox.width;
    double topA = hitBox.y;
    double bottomA = hitBox.y + hitBox.height;

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

void Entity::Damage(int damage)
{
    m_hp -= damage;

    if (IsDead())
    {
        m_hp = 0;
    }
}

bool Entity::IsDead()
{
    return (m_hp <= 0);
}

void Entity::SetHeld(bool isHeld)
{
    m_isHeld = isHeld;
}

bool Entity::IsHeld()
{
    return m_isHeld;
}
