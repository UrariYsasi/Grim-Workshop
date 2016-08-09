/*
    OpenGLWindowModule.cpp
    Peon Engine

    Declan Hopkins
    8/2/2016
*/

#include "PCH.hpp"
#include "OpenGLWindowModule.hpp"

namespace grim
{

OpenGLWindowModule::OpenGLWindowModule(Engine* const engine, const std::string& title, const uint16_t& width, const uint16_t& height, const bool& isFullscreen) :
    m_engine(engine),
    m_window(nullptr),
    m_glContext(),
    m_title(title),
    m_size(width, height),
    m_isFullscreen(isFullscreen)
{
}

OpenGLWindowModule::~OpenGLWindowModule()
{
}

bool OpenGLWindowModule::Initialize()
{
    LOG() << "Window Module OpenGLWindowModule initializing...";

    if (m_engine == nullptr)
    {
        LOG_ERROR() << "No engine was provided for Window Module!";
        return false;
    }

    // Initialize the SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        LOG_ERROR() << "SDL video failed to initialize! SDL error: " << SDL_GetError();
        return false;
    }

    // Create the window
    m_window = SDL_CreateWindow(
        m_title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_size.x,
        m_size.y,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (m_window == nullptr)
    {
        LOG_ERROR() << "Window could not be created! SDL error: " << SDL_GetError();
        return false;
    }

    // Set fullscreen mode
    if (m_isFullscreen)
    {
        SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
    }

    // Create the OpenGL Context
    m_glContext = SDL_GL_CreateContext(m_window);

    // Setup OpenGL profile and version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Turn VSYNC off
    SDL_GL_SetSwapInterval(0);

    LOG() << "Window Module OpenGLWindowModule initialized.";
    return true;
}

void OpenGLWindowModule::Terminate()
{
    LOG() << "Window Module OpenGLWindowModule terminating...";

    // Delete the OpenGL context
    SDL_GL_DeleteContext(m_glContext);

    // Delete the SDL window
    SDL_DestroyWindow(m_window);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);

    // If there are no SDL subsystems running, we need to terminate SDL2.
    if (!SDL_WasInit(SDL_INIT_EVERYTHING))
    {
        SDL_Quit();
    }

    LOG() << "Window Module OpenGLWindowModule terminated.";
}

void OpenGLWindowModule::HandleWindowEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            m_engine->Stop();
        }
    }
}

void OpenGLWindowModule::Display()
{
    SDL_GL_SwapWindow(m_window);
}

void OpenGLWindowModule::SetSize(const glm::ivec2& size)
{
    SDL_SetWindowSize(m_window, size.x, size.y);
}

void OpenGLWindowModule::SetTitle(const std::string& title)
{
    SDL_SetWindowTitle(m_window, title.c_str());
}

glm::ivec2 OpenGLWindowModule::GetSize() const
{
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(m_window, &width, &height);

    return glm::ivec2(width, height);
}

std::string OpenGLWindowModule::GetTitle() const
{
    return SDL_GetWindowTitle(m_window);
}

}