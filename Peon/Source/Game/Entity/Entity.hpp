#pragma once

class Game;

class Entity
{
public:
    Entity(Game* game, const glm::vec2& position, int entityID);
    virtual ~Entity();

    Game* GetGame();
    int GetEntityID();
    glm::vec2 GetPosition() const;
    glm::vec2 GetOrigin() const;
    glm::vec2 GetPositionOffset() const;
    void SetPosition(const glm::vec2& position);
    void SetPositionOffset(const glm::vec2& positionOffset);
    bool IsDeleted() const;
    grim::Rect GetHitBox() const;

    virtual void Update(double deltaTime) = 0;
    virtual void Render(grim::SpriteBatch& spriteBatch);

    void Delete();
    bool IsCollidingWithRect(const grim::Rect& rect) const;

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
    const glm::vec2 SPRITE_SIZE; // TODO: Do something with this

    Game* m_game;
    int m_entityID;
    glm::vec2 m_position;
    glm::vec2 m_origin;
    glm::vec2 m_positionOffset;
    bool m_isDeleted;
    grim::Rect m_hitBox;
    grim::Rect m_selectionHitBox;
    int m_hp;
    bool m_isHeld;

    std::unique_ptr<grim::Sprite> m_sprite;
};
