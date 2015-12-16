#pragma once
#include "PCH.hpp"
#include "Vector2D.hpp"

class Game;

class Input
{
    public:
        Input(Game* const game);
        ~Input();

        bool GetKey(const int& key);
        bool GetKeyPress(const int& key);
        bool GetKeyRelease(const int& key);
        bool GetMouseButton(const int& button);
        bool GetMouseButtonPress(const int& button);
        bool GetMouseButtonRelease(const int& button);
        Vector2D GetMousePosition() const;
        bool IsBoxSelecting() const;
        SDL_Rect GetBoxSelection() const;

        void Update();

    private:
        Game* m_game;
        bool m_currentKeys[256];
        bool m_downKeys[256];
        bool m_upKeys[256];
        bool m_currentMouseButtons[5];
        bool m_downMouseButtons[5];
        bool m_upMouseButtons[5];
        Vector2D m_mousePosition;
        bool m_isBoxSelecting;
        SDL_Rect m_boxSelection;
};