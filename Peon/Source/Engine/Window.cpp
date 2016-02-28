#include "PCH.hpp"
#include "Window.hpp"

Window::Window(const int& width, const int& height, const std::string& title) :
    m_size(Vector2D(width, height)),
    m_title(title)
{
}

Window::~Window()
{
    // Delete the OpenGL Context
    SDL_GL_DeleteContext(m_glContext);

    // Delete the SDL Window
    SDL_DestroyWindow(m_SDLWindow);
}

SDL_Window* Window::GetSDLWindow() const
{
    return m_SDLWindow;
}

void Window::SetSize(const Vector2D& size)
{
    m_size = size;
    SDL_SetWindowSize(m_SDLWindow, (int)size.x, (int)size.y);
}

Vector2D Window::GetSize() const
{
    return m_size;
}

std::string Window::GetTitle() const
{
    return m_title;
}

void Window::SetTitle(const std::string& title)
{
    m_title = title;
    SDL_SetWindowTitle(m_SDLWindow, title.c_str());
}


int Window::Initialize()
{
    // Create the SDL Window
    m_SDLWindow = SDL_CreateWindow(
        m_title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        (int)m_size.x,
        (int)m_size.y,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (m_SDLWindow == nullptr)
    {
        SDL_Log("Window could not initialize! SDL error: %s\n", SDL_GetError());
        return FAILURE;
    }

    // Create the OpenGL Context
    m_glContext = SDL_GL_CreateContext(m_SDLWindow);

    return SUCCESS;
}

void Window::SwapWindow()
{
    SDL_GL_SwapWindow(m_SDLWindow);
}