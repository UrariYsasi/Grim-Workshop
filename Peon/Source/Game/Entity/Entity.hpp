#pragma once

class Game;

class Entity
{
public:
    Entity(Game* game, Vector2D position);
    virtual ~Entity();

    Game* GetGame();
    Vector2D GetPosition() const;
    Vector2D GetPositionOffset() const;
    Vector2D GetPositionCenter() const;
    void SetPosition(const Vector2D& position);
    void SetPositionOffset(const Vector2D& positionOffset);
    bool IsDeleted() const;
    Rectangle GetHitBox() const;

    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;

    void Delete();
    bool IsCollidingWithRect(const Rectangle& rect) const;

protected:
    const Vector2D SPRITE_SIZE; // TODO: Do something with this

    Game* m_game;
    Vector2D m_position;
    Vector2D m_positionOffset;
    bool m_isDeleted;
    Rectangle m_hitBox;
};
