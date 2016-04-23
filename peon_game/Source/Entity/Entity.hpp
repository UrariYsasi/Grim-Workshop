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
    Entity(Game* game, const glm::vec2& position, EntityID ID);
    virtual ~Entity();

    virtual void Update(float deltaTime);
    virtual void Render(grim::graphics::SpriteBatch& spriteBatch);
    void Delete();

    Game* GetGame();
    EntityID GetID();
    glm::vec2 GetPosition() const;
    glm::vec2 GetOrigin() const;
    glm::vec2 GetPositionOffset() const;
    void SetPosition(const glm::vec2& position);
    void SetPositionOffset(const glm::vec2& positionOffset);
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
    glm::vec2 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_rotation;
    glm::vec2 m_origin;
    glm::vec2 m_positionOffset;
    bool m_isDeleted;
    grim::graphics::Rect m_hitBox;
    int m_hp;
    bool m_isHeld;

    uint32_t m_consumeStartTime;
    bool m_isBeingConsumed;
    Obelisk* m_consumer;
    glm::vec2 m_start;
    glm::vec2 m_end;

    Direction m_direction;
    std::unique_ptr<grim::graphics::Sprite> m_sprite;
};
