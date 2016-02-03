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
    // Is it currently set?
    return (m_currentKeyboardState[SDL_GetScancodeFromKey(key)] == 1);
}

bool Input::GetKeyPress(const int& key)
{
    // Not set before, but is set now?
    return (m_lastKeyboardState[SDL_GetScancodeFromKey(key)] == 0) && GetKey(key);
}

bool Input::GetKeyRelease(const int& key)
{
    // Set before, but not set now?
    return (m_lastKeyboardState[SDL_GetScancodeFromKey(key)] == 1) && !GetKey(key);
}

bool Input::GetMouseButton(const int& button)
{
    // Is this button down?
    return ((SDL_BUTTON(button) & m_currentMouseState) != 0);
}

bool Input::GetMouseButtonPress(const int& button)
{
    // Not down before, but down now?
    return ((SDL_BUTTON(button) & m_lastMouseState) == 0) && GetMouseButton(button);
}

bool Input::GetMouseButtonRelease(const int& button)
{
    // Down before, but not down now?
    return ((SDL_BUTTON(button) & m_lastMouseState) != 0) && !GetMouseButton(button);
}

Vector2D Input::GetMousePosition() const
{
    return m_mousePosition;
}

void Input::Update()
{
    int x, y;

    // This calls SDL_PumpEvents for us, but will tell is if a quit event is received
    if (SDL_QuitRequested())
    {
        m_game->Terminate();
        return;
    }

    // Save last state, get current state and position
    m_lastMouseState = m_currentMouseState;
    m_currentMouseState = SDL_GetMouseState(&x, &y);
    m_mousePosition = Vector2D(x, y);

    // Save last state, get current state
    m_lastKeyboardState = m_currentKeyboardState;
    m_currentKeyboardState = SDL_GetKeyboardState(NULL);

    // If this is our first time we don't have a last state, that isn't fun
    if (m_lastKeyboardState == nullptr)
    {
        m_lastKeyboardState = m_currentKeyboardState;
    }
}
