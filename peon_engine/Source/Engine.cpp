#include "PCH.hpp"
#include "Engine.hpp"

namespace grim
{

Engine::Engine() :
    m_isRunning(false),
    m_frameCount(0),
    m_frameRate(0),
    m_gameStartTime(0),
    m_window(nullptr),
    m_renderer(nullptr),
    m_input(nullptr),
    m_ui(nullptr),
    m_audio(nullptr)
{
}

Engine::~Engine()
{
    TTF_Quit();

    if (grim::utility::Debug::IsFlagEnabled(grim::utility::MIX_AUDIO))
    {
        Mix_CloseAudio();
        Mix_Quit();
    }

    SDL_Quit();
}

uint8_t Engine::Initialize()
{
    grim::utility::Debug::EnableFlag(grim::utility::LOGGING | grim::utility::CHEAT);

    /*
        Initialize SDL
    */

    if (SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS)
    {
        grim::utility::Debug::LogError("SDL could not initialize! SDL error: %s", SDL_GetError());
        SDL_ClearError();
        return FAILURE;
    }

    /*
        Initialize SDL_mixer
    */

    if (grim::utility::Debug::IsFlagEnabled(grim::utility::MIX_AUDIO))
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != SUCCESS)
        {
            grim::utility::Debug::LogError("SDL_mixer could not initialize! SDL_mixer error: %s", Mix_GetError());
            return FAILURE;
        }

        // Set default volume
        Mix_Volume(-1, MIX_MAX_VOLUME);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 6);
    }

    /*
        Initialize SDL_ttf
    */

    if (TTF_Init() != SUCCESS)
    {
        grim::utility::Debug::Log("SDL_ttf could not initialize! SDL_ttf error: %s", TTF_GetError());
        return FAILURE;
    }

    /*
        Setup OpenGL profile and version
    */

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    /*
        Create and Initialize Services
    */

    m_window = std::make_unique<grim::graphics::Window>(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if (m_window->Initialize() != SUCCESS)
    {
        return FAILURE;
    }
    m_renderer = std::make_unique<grim::graphics::Renderer>();
    m_ui = std::make_unique<grim::ui::UserInterface>();
    m_input = std::make_unique<grim::ui::Input>();
    m_input->SetQuitCallback(std::bind(&Engine::Terminate, this));
    m_audio = grim::audio::CreateAudioService();

    return SUCCESS;
}

void Engine::Terminate()
{
    m_isRunning = false;
}

void Engine::Run()
{
    m_isRunning = true;
    m_gameStartTime = SDL_GetTicks();

    uint32_t frameStartTime = 0;
    uint32_t frameEndTime = 0;
    while (m_isRunning == true)
    {
        frameStartTime = SDL_GetTicks();
        float deltaTime = (frameStartTime - frameEndTime) / 1000.0f;
        frameEndTime = frameStartTime;

        m_input->Update();
        Update(deltaTime);
        Render();
        m_window->SwapWindow();

        m_frameCount++;
        m_frameRate = static_cast<uint16_t>(std::round(((float)m_frameCount / (SDL_GetTicks() - m_gameStartTime)) * 1000.0f));
    }
}

grim::audio::IAudio* Engine::GetAudio()
{
    return m_audio.get();
}

}