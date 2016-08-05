/*
    Engine.cpp
    Peon Engine

    Declan Hopkins
    8/1/2016
*/

#include "PCH.hpp"
#include "Engine.hpp"

namespace grim
{

Engine::Engine(IGame* const game) :
    m_isRunning(false),
    m_game(game),
    m_deltaTimeSeconds(0.0),
    m_timeModule(nullptr),
    m_windowModule(nullptr),
    m_rendererModule(nullptr)
{
}

bool Engine::Initialize()
{
    LOG() << "Engine initializing...";

    // Make sure that we have a game to run
    if (m_game == nullptr)
    {
        LOG_ERROR() << "No game was provided to the Engine!";
        return false;
    }

    /*
        Initialize modules
    */

    m_timeModule = ModuleFactory::CreateTimeModule();
    if (!m_timeModule->Initialize())
    {
        m_timeModule = nullptr;
        LOG_ERROR() << "Time Module failed to initialize!";
        return false;
    }

    m_windowModule = ModuleFactory::CreateWindowModule(this);
    if (!m_windowModule->Initialize())
    {
        m_windowModule = nullptr;
        LOG_ERROR() << "Window Module failed to initialize!";
        return false;
    }

    m_rendererModule = ModuleFactory::CreateRendererModule();
    if (!m_rendererModule->Initialize())
    {
        m_rendererModule = nullptr;
        LOG_ERROR() << "Renderer Module failed to initialize!";
        return false;
    }

    LOG() << "Engine initialized.";
    return true;
}

void Engine::Terminate()
{
    LOG() << "Engine terminating...";

    /*
        Terminate modules
    */

    if (m_timeModule != nullptr) { m_timeModule->Terminate(); }
    if (m_windowModule != nullptr) { m_windowModule->Terminate(); }
    if (m_rendererModule != nullptr) { m_rendererModule->Terminate(); }

    LOG() << "Engine terminated.";
}

void Engine::Run()
{
    m_isRunning = true;

    /*
        Engine loop
    */

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
    m_rendererModule->Clear();
    m_game->Render();
    m_rendererModule->Render();
    m_windowModule->Display();
}

double Engine::GetDeltaTimeSeconds() const
{
    return m_deltaTimeSeconds;
}

}