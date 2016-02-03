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
    const static int MAX_KEYBOARD_KEYS = 256;
    const static int MAX_MOUSE_BUTTONS = 256;

    Game* m_game; // TODO Engine should not reference game, only the other way around

    bool m_currentKeys[MAX_KEYBOARD_KEYS];
    bool m_downKeys[MAX_KEYBOARD_KEYS];
    bool m_upKeys[MAX_KEYBOARD_KEYS];
    bool m_currentMouseButtons[MAX_KEYBOARD_KEYS];
    bool m_downMouseButtons[MAX_KEYBOARD_KEYS];
    bool m_upMouseButtons[MAX_KEYBOARD_KEYS];
    Vector2D m_mousePosition;
};
