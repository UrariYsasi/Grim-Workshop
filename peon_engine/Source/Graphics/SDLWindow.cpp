#include "PCH.hpp"
#include "SDLWindow.hpp"

namespace grim
{

namespace graphics
{

SDLWindow::SDLWindow(const uint16_t& width, const uint16_t& height, const std::string& title) :
    m_SDLWindow(nullptr),
    m_size(width, height),
    m_title(title)
{
}

SDLWindow::~SDLWindow()
{
    // Delete the OpenGL Context
    SDL_GL_DeleteContext(m_glContext);

    // Delete the SDL Window
    SDL_DestroyWindow(m_SDLWindow);

    // Check for any errors regarding window destruction
    const char* error = SDL_GetError();
    SDL_ClearError();
    if (error != nullptr)
    {
        grim::utility::Debug::LogError("Failed to destroy window! SDL error: %s", error);
    }
}

SDL_Window* SDLWindow::GetSDLWindow() const
{
    return m_SDLWindow;
}

void SDLWindow::SetSize(const glm::vec2& size)
{
    m_size = size;
    SDL_SetWindowSize(m_SDLWindow, (int)size.x, (int)size.y);
}

glm::vec2 SDLWindow::GetSize() const
{
    return m_size;
}

std::string SDLWindow::GetTitle() const
{
    return m_title;
}

void SDLWindow::SetTitle(const std::string& title)
{
    m_title = title;
    SDL_SetWindowTitle(m_SDLWindow, title.c_str());
}

uint8_t SDLWindow::Initialize()
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
        grim::utility::Debug::LogError("Window could not initialize! SDL error: %s", SDL_GetError());
        SDL_ClearError();
        return FAILURE;
    }

    // Create the OpenGL Context and make it current
    m_glContext = SDL_GL_CreateContext(m_SDLWindow);

    // Turn VSYNC off
    SDL_GL_SetSwapInterval(0);

    // Initialize GL3W
    if (gl3wInit())
    {
        grim::utility::Debug::LogError("Gl3W failed to initialize!");
        return FAILURE;
    }

    if (!gl3wIsSupported(3, 2))
    {
        grim::utility::Debug::LogError("OpenGL 3.2 not supported!");
        return FAILURE;
    }

    grim::utility::Debug::Log("OpenGL version %s, GLSL version %s", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    return SUCCESS;
}

void SDLWindow::SwapWindow()
{
    SDL_GL_SwapWindow(m_SDLWindow);
}

}

}