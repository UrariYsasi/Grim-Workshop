#include "PCH.hpp"
#include "Input.hpp"
#include "../Game/Game.hpp"

Input::Input(Game* const game) :
    m_game(game),
    m_mousePosition(0, 0),
    m_isBoxSelecting(false),
    m_boxSelection(SDL_Rect{0, 0, 0, 0})
{
}

Input::~Input()
{
}

bool Input::GetKey(const int& key)
{
    if (key >= MAX_KEYS)
    {
        SDL_Log("Input::GetKey() failed! Key %d is out of range.", key);
        return false;
    }

    return m_currentKeys[key];
}

bool Input::GetKeyPress(const int& key)
{
    if (key >= MAX_KEYS)
    {
        SDL_Log("Input::GetKeyPress() failed! Key %d is out of range.", key);
        return false;
    }

    return m_downKeys[key];
}

bool Input::GetKeyRelease(const int& key)
{
    if (key >= MAX_KEYS)
    {
        SDL_Log("Input::GetKeyRelease() failed! Key %d is out of range.", key);
        return false;
    }

    return m_upKeys[key];
}

bool Input::GetMouseButton(const int& button)
{
    if (button >= MAX_MOUSE_BUTTONS)
    {
        SDL_Log("Input::GetMouseButton() failed! Button %d is out of range.", button);
        return false;
    }

    return m_currentMouseButtons[button];
}

bool Input::GetMouseButtonPress(const int& button)
{
    if (button >= MAX_MOUSE_BUTTONS)
    {
        SDL_Log("Input::GetMouseButtonPress() failed! Button %d is out of range.", button);
        return false;
    }

    return m_downMouseButtons[button];
}

bool Input::GetMouseButtonRelease(const int& button)
{
    if (button >= MAX_MOUSE_BUTTONS)
    {
        SDL_Log("Input::GetMouseButtonRelease() failed! Button %d is out of range.", button);
        return false;
    }

    return m_upMouseButtons[button];
}

Vector2D Input::GetMousePosition() const
{
    return m_mousePosition;
}

bool Input::IsBoxSelecting() const
{
    return m_isBoxSelecting;
}

SDL_Rect Input::GetBoxSelection() const
{
    return m_boxSelection;
}

void Input::Update()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    m_mousePosition = Vector2D(x, y);

    for (int i = 0; i < MAX_KEYS; i++)
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

    if(GetKeyPress(SDLK_ESCAPE))
    {
        m_game->Terminate();
    }

    if (GetMouseButton(SDL_BUTTON_LEFT))
    {
        if (!m_isBoxSelecting)
        {
            m_isBoxSelecting = true;

            m_boxSelection.x = (int)m_mousePosition.x;
            m_boxSelection.y = (int)m_mousePosition.y;
        }
        
        m_boxSelection.w = (int)m_mousePosition.x - m_boxSelection.x;
        m_boxSelection.h = (int)m_mousePosition.y - m_boxSelection.y;
    }
}

void Input::EndBoxSelection()
{
    m_isBoxSelecting = false;
}
