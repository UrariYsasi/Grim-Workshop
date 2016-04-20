#include "PCH.hpp"
#include "SDLWindow.hpp"

namespace grim
{

namespace graphics
{

SDLWindow::SDLWindow(const uint16_t& width, const uint16_t& height, const std::string& title, bool isFullScreen, bool isOpenGL) :
    m_SDLWindow(nullptr),
    m_size(width, height),
    m_title(title),
    m_isFullScreen(isFullScreen),
    m_isOpenGL(isOpenGL)
{
}

SDLWindow::~SDLWindow()
{
    // Delete the OpenGL Context
    SDL_GL_DeleteContext(m_glContext);

    // Delete the SDL Window
    SDL_DestroyWindow(m_SDLWindow);
}

bool SDLWindow::Initialize()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        grim::utility::Debug::LogError("SDL could not initialize! SDL error: %s", SDL_GetError());
        return false;
    }

    // Create the SDL Window
    uint32_t openGLFlag = (m_isOpenGL ? SDL_WINDOW_OPENGL : 0);
    m_SDLWindow = SDL_CreateWindow(
        m_title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        (int)m_size.x,
        (int)m_size.y,
        SDL_WINDOW_SHOWN | openGLFlag);

    if (m_SDLWindow == nullptr)
    {
        grim::utility::Debug::LogError("Window could not initialize! SDL error: %s", SDL_GetError());
        return false;
    }

    // Set fullscreen
    if (m_isFullScreen)
    {
        SDL_SetWindowFullscreen(m_SDLWindow, SDL_WINDOW_FULLSCREEN);
    }

    if (m_isOpenGL)
    {
        // Create the OpenGL Context
        m_glContext = SDL_GL_CreateContext(m_SDLWindow);

        // Setup OpenGL profile and version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        // Turn VSYNC off
        SDL_GL_SetSwapInterval(0);
    }

    grim::utility::Debug::LogError("Window module SDLWindow initialized.");
    return true;
}

void SDLWindow::SwapWindow()
{
    if (!m_isOpenGL) { return; }
    SDL_GL_SwapWindow(m_SDLWindow);
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

}

}