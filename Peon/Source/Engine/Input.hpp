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
        bool IsBoxSelecting() const;
        SDL_Rect GetBoxSelection() const;

        void Update();
        void EndBoxSelection();

    private:
        const static int MAX_KEYS = 256;
        const static int MAX_MOUSE_BUTTONS = 5;

        Game* m_game;
        const Uint8* m_lastKeyboardState;
        const Uint8* m_currentKeyboardState;
        Uint32 m_lastMouseState;
        Uint32 m_currentMouseState;
        Vector2D m_mousePosition;
        bool m_isBoxSelecting;
        SDL_Rect m_boxSelection;
};
