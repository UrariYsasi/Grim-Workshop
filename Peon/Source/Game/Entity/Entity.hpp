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
    Vector2D GetPositionOffset() const;
    Vector2D GetPositionCenter() const;
    void SetPosition(const Vector2D& position);
    void SetPositionOffset(const Vector2D& positionOffset);
    bool IsDeleted() const;
    Rectangle GetHitBox() const;

    virtual void Update(double deltaTime) = 0;
    virtual void Render();

    void Delete();
    bool IsCollidingWithRect(const Rectangle& rect) const;

    /*
        Damage the entity.

        Different Entity types should handle this differently.
    */
    void Damage(int damage = 1);

    /*
        Checks if the Entity has died.

        An Entity is dead when its hp is <= 0.
    */
    bool IsDead();

protected:
    const Vector2D SPRITE_SIZE; // TODO: Do something with this

    Game* m_game;
    int m_entityID;
    Vector2D m_position;
    Vector2D m_origin;
    Vector2D m_positionOffset;
    bool m_isDeleted;
    Rectangle m_hitBox;
    int m_hp;
};
