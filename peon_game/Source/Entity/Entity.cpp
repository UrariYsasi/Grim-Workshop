#include "PCH.hpp"
#include "Entity.hpp"
#include "../Game.hpp"
#include "Obelisk.hpp"

Entity::Entity(Game* game, const glm::vec3& position, EntityID ID) :
    m_game(game),
    m_ID(ID),
    m_transform(position, glm::vec3(0.0f), glm::vec3(1.0f)),
    m_origin(0.0f, 0.0f, 0.0f),
    m_positionOffset(0.0f, 0.0f, 0.0f),
    m_isDeleted(false),
    m_hitBox(-16, -16, 16, 16),
    m_hp(3),
    m_isHeld(false),
    m_consumeStartTime(0),
    m_isBeingConsumed(false),
    m_consumer(nullptr),
    m_direction(Direction::RIGHT),
    m_sprite(nullptr)
{
}

Entity::~Entity()
{
}

Game* Entity::GetGame()
{
    return m_game;
}

EntityID Entity::GetID()
{
    return m_ID;
}

grim::graphics::Transform Entity::GetTransform() const
{
    return m_transform;
}

glm::vec3 Entity::GetOrigin() const
{
    return m_origin;
}

glm::vec3 Entity::GetPositionOffset() const
{
    return m_positionOffset;
}

void Entity::SetTransform(const grim::graphics::Transform& transform)
{
    m_transform = transform;
}

void Entity::SetPositionOffset(const glm::vec3& positionOffset)
{
    m_positionOffset = positionOffset;
}

bool Entity::IsDeleted() const
{
    return m_isDeleted;
}

grim::graphics::Rect Entity::GetHitBox() const
{
    grim::graphics::Rect bounds;
    bounds.x = m_transform.position.x + m_hitBox.x;
    bounds.y = m_transform.position.y + m_hitBox.y;
    bounds.width = m_hitBox.width;
    bounds.height = m_hitBox.height;

    return bounds;
}

void Entity::Update(float deltaTime)
{
    if (m_isBeingConsumed)
    {
        Delete();
    }
}

void Entity::Render()
{
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
bool Entity::IsCollidingWithRect(const grim::graphics::Rect& rect) const
{
    grim::graphics::Rect hitBox = GetHitBox();

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

void Entity::Consume(Obelisk* obelisk)
{
    m_isBeingConsumed = true;
}

void Entity::SetDirection(const Direction& direction)
{
    m_direction = direction;
}

Entity::Direction Entity::GetDirection() const
{
    return m_direction;
}