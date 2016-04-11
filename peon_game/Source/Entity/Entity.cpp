#include "PCH.hpp"
#include "Entity.hpp"
#include "../Game.hpp"
#include "Obelisk.hpp"

Entity::Entity(Game* game, const glm::vec2& position, int entityID) :
    m_game(game),
    m_entityID(entityID),
    m_position(position),
    m_scale(32.0f, 32.0f, 1.0f),
    m_origin(0, 0),
    m_positionOffset(0, 0),
    m_isDeleted(false),
    m_hitBox(-16, -16, 16, 16),
    m_selectionHitBox(-16, -16, 16, 16),
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

int Entity::GetEntityID()
{
    return m_entityID;
}

glm::vec2 Entity::GetPosition() const
{
    return m_position;
}

glm::vec2 Entity::GetOrigin() const
{
    return m_origin;
}

glm::vec2 Entity::GetPositionOffset() const
{
    return m_positionOffset;
}

void Entity::SetPosition(const glm::vec2& position)
{
    m_position = position;
}

void Entity::SetPositionOffset(const glm::vec2& positionOffset)
{
    m_positionOffset = positionOffset;
}

bool Entity::IsDeleted() const
{
    return m_isDeleted;
}

grim::graphics::Rect Entity::GetHitBox() const
{
    return grim::graphics::Rect(m_position.x + m_hitBox.x, m_position.y + m_hitBox.y, m_hitBox.width, m_hitBox.height);
}

void Entity::Update(float deltaTime)
{
    if (m_isBeingConsumed)
    {
        m_position = (m_position + 0.03f * (m_end - m_start));

        if (glm::distance(m_position, m_end) <= 5.0f)
        {
            Delete();
        }
    }
}

void Entity::Render(grim::graphics::SpriteBatch& spriteBatch)
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
    m_consumer = obelisk;
    m_start = m_position;
    m_end = m_consumer->GetPosition() + glm::vec2(0.0f, -235.0f);
    m_sprite->color = grim::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f);
}

void Entity::SetDirection(const Direction& direction)
{
    m_direction = direction;
}

Entity::Direction Entity::GetDirection() const
{
    return m_direction;
}