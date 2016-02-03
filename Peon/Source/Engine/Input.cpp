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
    return m_currentKeys[key];
}

bool Input::GetKeyPress(const int& key)
{
    return m_downKeys[key];
}

bool Input::GetKeyRelease(const int& key)
{
    return m_upKeys[key];
}

bool Input::GetMouseButton(const int& button)
{
    return m_currentMouseButtons[button];
}

bool Input::GetMouseButtonPress(const int& button)
{
    return m_downMouseButtons[button];
}

bool Input::GetMouseButtonRelease(const int& button)
{
    return m_upMouseButtons[button];
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

    m_downKeys.clear();
    m_upKeys.clear();
    m_downMouseButtons.clear();
    m_upMouseButtons.clear();

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        int key = event.key.keysym.sym;
        int mouseButton = event.button.button;

        if (event.type == SDL_KEYDOWN)
        {
            if (!m_currentKeys[key])
            {
                m_downKeys[key] = true;
            }

            m_currentKeys[key] = true;
        }
        else if (event.type == SDL_KEYUP)
        {
            m_upKeys[key] = true;
            m_currentKeys[key] = false;
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