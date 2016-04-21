#pragma once

namespace grim
{

namespace ui
{

class SDLInput : public IInput
{
public:
    SDLInput();
    ~SDLInput();

    virtual bool Initialize();
    virtual void Terminate();
    virtual void Update();
    virtual void InvalidateMouseButtonPress(int button);

    virtual void SetQuitCallback(std::function<void()> quitCallback);
    virtual bool GetKey(int key);
    virtual bool GetKeyPress(int key);
    virtual bool GetKeyRelease(int key);
    virtual bool GetMouseButton(int button);
    virtual bool GetMouseButtonPress(int button);
    virtual bool GetMouseButtonRelease(int button);
    virtual glm::vec2 GetMousePosition() const;

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

    std::function<void()> m_quitCallback;
};

}

}