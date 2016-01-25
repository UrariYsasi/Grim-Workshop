#pragma once
#include "../../PCH.hpp"
#include "../../Engine/Vector2D.hpp"

class Game;

class Entity
{
public:
    Entity(Game* game, Vector2D position);
    virtual ~Entity();

    Game* GetGame();
    Vector2D GetPosition() const;
    void SetPosition(const Vector2D& position);
    bool IsDeleted() const;

    virtual void Update() = 0;
    virtual void Render() = 0;
    void Delete();
    bool IsCollidingWithRect(const SDL_Rect& rect) const;

protected:
    Game* m_game;
    Vector2D m_position;
    bool m_isDeleted;
};
