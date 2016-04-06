#pragma once

class Game;

namespace grim
{

namespace ui
{

class Input
{
public:
    Input();
    ~Input();

    bool GetKey(int key);
    bool GetKeyPress(int key);
    bool GetKeyRelease(int key);
    bool GetMouseButton(int button);
    bool GetMouseButtonPress(int button);
    bool GetMouseButtonRelease(int button);
    glm::vec2 GetMousePosition() const;

    void SetQuitCallback(std::function<void()> quitCallback);

    void Update();

private:
    const static int MAX_KEYBOARD_KEYS = 256;
    const static int MAX_MOUSE_BUTTONS = 256;

    bool m_currentKeys[MAX_KEYBOARD_KEYS];
    bool m_downKeys[MAX_KEYBOARD_KEYS];
    bool m_upKeys[MAX_KEYBOARD_KEYS];
    bool m_currentMouseButtons[MAX_KEYBOARD_KEYS];
    bool m_downMouseButtons[MAX_KEYBOARD_KEYS];
    bool m_upMouseButtons[MAX_KEYBOARD_KEYS];
    glm::vec2 m_mousePosition;

    std::function<void(void)> m_quitCallback;
};

}

}