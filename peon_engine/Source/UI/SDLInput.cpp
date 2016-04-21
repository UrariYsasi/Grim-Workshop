#include "PCH.hpp"
#include "SDLInput.hpp"

namespace grim
{

namespace ui
{

SDLInput::SDLInput() :
    m_mousePosition(0),
    m_quitCallback(nullptr)
{
}

SDLInput::~SDLInput()
{
}

bool SDLInput::Initialize()
{
    std::fill(m_currentKeys, m_currentKeys + MAX_KEYBOARD_KEYS, false);
    std::fill(m_downKeys, m_downKeys + MAX_KEYBOARD_KEYS, false);
    std::fill(m_upKeys, m_upKeys + MAX_KEYBOARD_KEYS, false);
    std::fill(m_currentMouseButtons, m_currentMouseButtons + MAX_MOUSE_BUTTONS, false);
    std::fill(m_downMouseButtons, m_downMouseButtons + MAX_MOUSE_BUTTONS, false);
    std::fill(m_upMouseButtons, m_upMouseButtons + MAX_MOUSE_BUTTONS, false);

    grim::utility::Debug::LogError("Input module SDLInput initialized.");
    return true;
}

void SDLInput::Terminate()
{
    grim::utility::Debug::LogError("Input module SDLInput initialized.");
}

void SDLInput::Update()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    m_mousePosition = glm::vec2(x, y);

    for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
    {
        m_downKeys[i] = false;
        m_upKeys[i] = false;
    }

    for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
    {
        m_downMouseButtons[i] = false;
        m_upMouseButtons[i] = false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        int key = event.key.keysym.sym;
        int mouseButton = event.button.button;

        if (event.type == SDL_KEYDOWN)
        {
            if (!m_currentKeys[SDL_GetScancodeFromKey(key)])
            {
                m_downKeys[SDL_GetScancodeFromKey(key)] = true;
            }

            m_currentKeys[SDL_GetScancodeFromKey(key)] = true;
        }
        else if (event.type == SDL_KEYUP)
        {
            m_upKeys[SDL_GetScancodeFromKey(key)] = true;
            m_currentKeys[SDL_GetScancodeFromKey(key)] = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (!m_currentMouseButtons[mouseButton])
            {
                m_downMouseButtons[mouseButton] = true;
            }

            m_currentMouseButtons[mouseButton] = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            m_upMouseButtons[mouseButton] = true;
            m_currentMouseButtons[mouseButton] = false;
        }
        else if (event.type == SDL_QUIT)
        {
            if (m_quitCallback != nullptr)
            {
                m_quitCallback();
            }
        }
    }
}

void SDLInput::InvalidateMouseButtonPress(int button)
{
    if (SDL_GetScancodeFromKey(button) >= MAX_MOUSE_BUTTONS)
    {
        return;
    }

    m_downMouseButtons[button] = false;
}

bool SDLInput::GetKey(int key)
{
    if (SDL_GetScancodeFromKey(key) >= MAX_KEYBOARD_KEYS)
    {
        return false;
    }

    return m_currentKeys[SDL_GetScancodeFromKey(key)];
}

bool SDLInput::GetKeyPress(int key)
{
    if (SDL_GetScancodeFromKey(key) >= MAX_KEYBOARD_KEYS)
    {
        return false;
    }

    return m_downKeys[SDL_GetScancodeFromKey(key)];
}

bool SDLInput::GetKeyRelease(int key)
{
    if (SDL_GetScancodeFromKey(key) >= MAX_KEYBOARD_KEYS)
    {
        return false;
    }

    return m_upKeys[SDL_GetScancodeFromKey(key)];
}

bool SDLInput::GetMouseButton(int button)
{
    if (SDL_GetScancodeFromKey(button) >= MAX_MOUSE_BUTTONS)
    {
        return false;
    }

    return m_currentMouseButtons[button];
}

bool SDLInput::GetMouseButtonPress(int button)
{
    if (SDL_GetScancodeFromKey(button) >= MAX_MOUSE_BUTTONS)
    {
        return false;
    }

    return m_downMouseButtons[button];
}

bool SDLInput::GetMouseButtonRelease(int button)
{
    if (SDL_GetScancodeFromKey(button) >= MAX_MOUSE_BUTTONS)
    {
        return false;
    }

    return m_upMouseButtons[button];
}

glm::vec2 SDLInput::GetMousePosition() const
{
    return m_mousePosition;
}

void SDLInput::SetQuitCallback(std::function<void()> quitCallback)
{
    m_quitCallback = quitCallback;
}

}

}