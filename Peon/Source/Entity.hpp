#pragma once
#include "PCH.hpp"
#include "Vector2D.hpp"

class Game;

class Entity
{
    public:
        Entity(Game* game, Vector2D position);
        virtual ~Entity();

        Vector2D GetPosition() const;
        void SetPosition(const Vector2D& position);
        SDL_Rect GetHitbox() const;
        void SetHitbox(const SDL_Rect& hitbox);

        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
        Game* m_game;
        Vector2D m_position;
        SDL_Rect m_hitbox;
};