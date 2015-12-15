#include "PCH.hpp"
#include "Window.hpp"

Window::Window(const int& width, const int& height, const std::string& title) :
    m_width(width),
    m_height(height),
    m_title(title)
{
    m_SDLWindow = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
    if (m_SDLWindow == nullptr)
    {
        std::cerr << "Window could not be created! SDL error: " << SDL_GetError() << std::endl;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(m_SDLWindow);
}