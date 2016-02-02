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
        std::map<int, bool> m_currentKeys;
        std::map<int, bool> m_downKeys;
        std::map<int, bool> m_upKeys;
        std::map<int, bool> m_currentMouseButtons;
        std::map<int, bool> m_downMouseButtons;
        std::map<int, bool> m_upMouseButtons;
        Vector2D m_mousePosition;
        bool m_isBoxSelecting;
        SDL_Rect m_boxSelection;
};
