#include "PCH.hpp"
#include "Input.hpp"
#include "../Game/Game.hpp"

Input::Input(Game* const game) :
    m_game(game),
    m_mousePosition(0, 0)
{
}

Input::~Input()
{
}

bool Input::GetKey(const int& key)
{
    if(m_currentKeys[SDL_GetScancodeFromKey(key)])
    {
        return m_currentKeys[SDL_GetScancodeFromKey(key)];
    }

    return false;
}

bool Input::GetKeyPress(const int& key)
{
    if(m_downKeys[SDL_GetScancodeFromKey(key)])
    {
        return m_downKeys[SDL_GetScancodeFromKey(key)];
    }

    return false;
}

bool Input::GetKeyRelease(const int& key)
{
    if(m_upKeys[SDL_GetScancodeFromKey(key)])
    {
        return m_upKeys[SDL_GetScancodeFromKey(key)];
    }

    return false;
}

bool Input::GetMouseButton(const int& button)
{
    if(m_currentMouseButtons[button])
    {
        return m_currentMouseButtons[button];
    }

    return false;
}

bool Input::GetMouseButtonPress(const int& button)
{
    if(m_downMouseButtons[button])
    {
        return m_downMouseButtons[button];
    }

    return false;
}

bool Input::GetMouseButtonRelease(const int& button)
{
    if(m_upMouseButtons[button])
    {
        return m_upMouseButtons[button];
    }

    return false;
}

Vector2D Input::GetMousePosition() const
{
    return m_mousePosition;
}

void Input::Update()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    m_mousePosition = Vector2D(x, y);

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
            m_game->Terminate();
        }
    }
}
