#include "PCH.hpp"
#include "Input.hpp"
#include "Game.hpp"

Input::Input(Game* const game) :
    m_game(game)
{
}

Input::~Input()
{
}

void Input::Update()
{
    for (int i = 0; i < 256; i++)
    {
        m_downKeys[i] = false;
        m_upKeys[i] = false;
    }

    for (int i = 0; i < 5; i++)
    {
        m_downMouseButtons[i] = false;
        m_upMouseButtons[i] = false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        int key = event.key.keysym.scancode;
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