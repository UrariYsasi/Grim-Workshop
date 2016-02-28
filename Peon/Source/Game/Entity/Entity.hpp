#pragma once

class Game;

class Entity
{
public:
    Entity(Game* game, const Vector2D& position, int entityID);
    virtual ~Entity();

    Game* GetGame();
    int GetEntityID();
    Vector2D GetPosition() const;
    Vector2D GetOrigin() const;
    Vector2D GetPositionOffset() const;
    void SetPosition(const Vector2D& position);
    void SetPositionOffset(const Vector2D& positionOffset);
    bool IsDeleted() const;
    Rect GetHitBox() const;

    virtual void Update(double deltaTime) = 0;
    virtual void Render();

    void Delete();
    bool IsCollidingWithRect(const Rect& rect) const;

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

protected:
    const Vector2D SPRITE_SIZE; // TODO: Do something with this

    Game* m_game;
    int m_entityID;
    Vector2D m_position;
    Vector2D m_origin;
    Vector2D m_positionOffset;
    bool m_isDeleted;
    Rect m_hitBox;
    Rect m_selectionHitBox;
    int m_hp;
    bool m_isHeld;
};
