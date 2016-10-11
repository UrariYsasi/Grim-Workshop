/*
    Engine.cpp
    Engine

    Declan Hopkins
    8/31/2016
*/

#include "PCH.hpp"
#include "Engine.hpp"

namespace grim
{

Engine::Engine(IGame* const game) :
    m_isRunning(false),
    m_game(game),
    m_deltaTimeSeconds(0.0),
    m_frameCount(0),
    m_frameRate(0),
    m_timeModule(nullptr),
    m_fileModule(nullptr),
    m_assetModule(nullptr),
    m_inputModule(nullptr),
    m_windowModule(nullptr),
    m_renderer(nullptr),
    m_audio(nullptr)
{
}

Engine::~Engine()
{
}

bool Engine::Initialize()
{
    LOG() << "Engine initializing...";

    /*
        Create and Initialize Modules
    */

    m_timeModule = ModuleFactory::CreateTimeModule();
    if (!m_timeModule->Initialize())
    {
        m_timeModule = nullptr;
        LOG_ERROR() << "Time Module failed to initialize!";
        return false;
    }

    m_fileModule = ModuleFactory::CreateFileModule();
    if (!m_fileModule->Initialize())
    {
        m_fileModule = nullptr;
        LOG_ERROR() << "File Module failed to initialize!";
        return false;
    }

    m_assetModule = ModuleFactory::CreateAssetModule(this);
    if (!m_assetModule->Initialize())
    {
        m_assetModule = nullptr;
        LOG_ERROR() << "Asset Module failed to initialize!";
        return false;
    }

    m_windowModule = ModuleFactory::CreateWindowModule(this);
    if (!m_windowModule->Initialize())
    {
        m_windowModule = nullptr;
        LOG_ERROR() << "Window Module failed to initialize!";
        return false;
    }

    m_inputModule = ModuleFactory::CreateInputModule();
    if (!m_inputModule->Initialize())
    {
        m_inputModule = nullptr;
        LOG_ERROR() << "Input Module failed to initialize!";
        return false;
    }

    /*
    m_rendererModule = ModuleFactory::CreateRendererModule();
    if (!m_rendererModule->Initialize())
    {
        m_rendererModule = nullptr;
        LOG_ERROR() << "Renderer Module failed to initialize!";
        return false;
    }
    */

    // LEGACY

    m_renderer = grim::graphics::CreateRendererService();
    if (!m_renderer->Initialize()) { return false; }

    m_audio = grim::audio::CreateAudioService();
    if (!m_audio->Initialize()) { return false; }

    LOG() << "Engine initialized.";
    return true;
}

void Engine::Terminate()
{
    LOG() << "Engine terminating...";

    /*
        Terminate modules
    */

    // LEGACY
    m_audio->Terminate();
    m_renderer->Terminate();

    if (m_timeModule != nullptr) { m_timeModule->Terminate(); }
    if (m_fileModule != nullptr) { m_fileModule->Terminate(); }
    if (m_assetModule != nullptr) { m_assetModule->Terminate(); }
    if (m_inputModule != nullptr) { m_inputModule->Terminate(); }
    if (m_windowModule != nullptr) { m_windowModule->Terminate(); }
    //if (m_rendererModule != nullptr) { m_rendererModule->Terminate(); }

    LOG() << "Engine terminated.";
}

void Engine::Run()
{
    m_isRunning = true;

    double frameStartTimeSeconds = 0.0;
    double frameEndTimeSeconds = 0.0;

    while (m_isRunning)
    {
        m_deltaTimeSeconds = frameEndTimeSeconds - frameStartTimeSeconds;
        frameStartTimeSeconds = m_timeModule->GetTimeSeconds();

        Update();
        Render();

        frameEndTimeSeconds = m_timeModule->GetTimeSeconds();
    }
}

void Engine::Stop()
{
    m_isRunning = false;
}

void Engine::Update()
{
    m_windowModule->HandleWindowEvents();
    m_game->Update();
}

void Engine::Render()
{
    m_renderer->Clear();
    m_game->Render();
    m_renderer->Render();
    m_windowModule->Display();
}

grim::graphics::IRenderer* Engine::GetRenderer()
{
    return m_renderer.get();
}

grim::audio::IAudio* Engine::GetAudio()
{
    return m_audio.get();
}

utility::ITimeModule* Engine::GetTimeModule()
{
    return m_timeModule.get();
}

platform::IFileModule* Engine::GetFileModule()
{
    return m_fileModule.get();
}

assets::IAssetModule* Engine::GetAssetModule()
{
    return m_assetModule.get();
}

ui::IInputModule* Engine::GetInputModule()
{
    return m_inputModule.get();
}

graphics::IWindowModule* Engine::GetWindowModule()
{
    return m_windowModule.get();
}

}