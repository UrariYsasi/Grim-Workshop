#pragma once

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

        void Update();

    private:
        Game* m_game; // TODO Engine should not reference game, only the other way around
        const Uint8* m_lastKeyboardState;
        const Uint8* m_currentKeyboardState;
        Uint32 m_lastMouseState;
        Uint32 m_currentMouseState;
        Vector2D m_mousePosition;
};
