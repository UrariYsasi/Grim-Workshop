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
    m_audio(nullptr),
    m_timeScale(1.0f)
{
}

Engine::~Engine()
{
    m_audio->Terminate();
    m_input->Terminate();
    m_ui->Terminate();
    m_renderer->Terminate();
    m_window->Terminate();
}

bool Engine::Initialize()
{
    grim::utility::Debug::EnableFlag(grim::utility::LOGGING);

    /*
        Create and Initialize Modules
    */

    m_window = grim::graphics::CreateWindowService(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, IS_WINDOW_FULLSCREEN, IS_WINDOW_OPENGL);
    if (!m_window->Initialize()) { return false; }

    m_renderer = grim::graphics::CreateRendererService();
    if (!m_renderer->Initialize()) { return false; }

    m_ui = grim::ui::CreateUIService(this);
    if (!m_ui->Initialize()) { return false;  }

    m_input = grim::ui::CreateInputService();
    m_input->SetQuitCallback(std::bind(&Engine::Terminate, this));
    if (!m_input->Initialize()) { return false; }

    m_audio = grim::audio::CreateAudioService();
    if (!m_audio->Initialize()) { return false; }

    return true;
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
    while (m_isRunning)
    {
        frameStartTime = SDL_GetTicks();
        float deltaTime = (frameStartTime - frameEndTime) / 1000.0f;
        frameEndTime = frameStartTime;

        m_input->Update();
        Update(deltaTime);
        Render();
        //m_renderer->Render();
        m_window->SwapWindow();

        m_frameCount++;
        m_frameRate = static_cast<uint16_t>(std::round(((float)m_frameCount / (SDL_GetTicks() - m_gameStartTime)) * 1000.0f));
    }
}

void Engine::SetTimeScale(float scale)
{
    m_timeScale = scale;
}

grim::graphics::IWindow* Engine::GetWindow()
{
    return m_window.get();
}

grim::graphics::IRenderer* Engine::GetRenderer()
{
    return m_renderer.get();
}

grim::audio::IAudio* Engine::GetAudio()
{
    return m_audio.get();
}

grim::ui::IInput* Engine::GetInput()
{
    return m_input.get();
}

grim::ui::IUserInterface* Engine::GetUI()
{
    return m_ui.get();
}

uint32_t Engine::GetTime()
{
    return (SDL_GetTicks() - m_gameStartTime) * m_timeScale;
}

}