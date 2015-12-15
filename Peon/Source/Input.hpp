#pragma once
#include "PCH.hpp"

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

        void Update();

    private:
        Game* m_game;
        bool m_currentKeys[256];
        bool m_downKeys[256];
        bool m_upKeys[256];
        bool m_currentMouseButtons[5];
        bool m_downMouseButtons[256];
        bool m_upMouseButtons[256];
};

inline bool Input::GetKey(const int& key)
{
    return m_currentKeys[key];
}

inline bool Input::GetKeyPress(const int& key)
{
    return m_downKeys[key];
}

inline bool Input::GetKeyRelease(const int& key)
{
    return m_upKeys[key];
}

inline bool Input::GetMouseButton(const int& button)
{
    return m_currentMouseButtons[button];
}

inline bool Input::GetMouseButtonPress(const int& button)
{
    return m_downMouseButtons[button];
}

inline bool Input::GetMouseButtonRelease(const int& button)
{
    return m_upMouseButtons[button];
}