#pragma once

class Game;
class Obelisk;

class Entity
{
public:
    enum class Direction
    {
        LEFT,
        RIGHT
    };

public:
    Entity(Game* game, const glm::vec3& position, EntityID ID);
    virtual ~Entity();

    virtual void Update(float deltaTime);
    virtual void Render();
    void Delete();

    void SetTransform(const grim::graphics::Transform& transform);
    void SetPositionOffset(const glm::vec3& positionOffset);
    Game* GetGame();
    EntityID GetID();
    grim::graphics::Transform GetTransform() const;
    glm::vec3 GetOrigin() const;
    glm::vec3 GetPositionOffset() const;
    bool IsDeleted() const;
    grim::graphics::Rect GetHitBox() const;

    bool IsCollidingWithRect(const grim::graphics::Rect& rect) const;

    /*
        Damage the entity.

        Different Entity types should handle this differently.
    */
    void Damage(int damage = 1);

    /*
        Check if this Entity has died.

        An Entity is dead when its hp is <= 0.
    */
    bool IsDead();

    /*
        Change whether or not this Entity is being held.
    */
    void SetHeld(bool isHeld);

    /*
        Check if this Entity is being held.
    */
    bool IsHeld();

    virtual void Consume(Obelisk* obelisk);

    void SetDirection(const Direction& direction);
    Direction GetDirection() const;

protected:
    Game* m_game;
    EntityID m_ID;
    grim::graphics::Transform m_transform;
    glm::vec3 m_rotation;
    glm::vec3 m_origin;
    glm::vec3 m_positionOffset;
    bool m_isDeleted;
    grim::graphics::Rect m_hitBox;
    int m_hp;
    bool m_isHeld;

    uint32_t m_consumeStartTime;
    bool m_isBeingConsumed;
    Obelisk* m_consumer;
    glm::vec3 m_start;
    glm::vec3 m_end;

    Direction m_direction;
    grim::graphics::Sprite m_sprite;
};
