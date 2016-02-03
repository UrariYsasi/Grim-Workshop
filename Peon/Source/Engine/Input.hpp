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
        std::map<int, bool> m_currentKeys;
        std::map<int, bool> m_downKeys;
        std::map<int, bool> m_upKeys;
        std::map<int, bool> m_currentMouseButtons;
        std::map<int, bool> m_downMouseButtons;
        std::map<int, bool> m_upMouseButtons;
        Vector2D m_mousePosition;
};
