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
    m_windowModule(nullptr),
    m_timeModule(nullptr)
{
}

bool Engine::Initialize()
{
    // Make sure that we have a game to run
    if (m_game == nullptr)
    {
        std::cout << "No game was provided to the Engine!" << std::endl;
        return false;
    }

    /*
        Initialize modules
    */

    m_timeModule = ModuleFactory::CreateTimeModule();
    if (!m_timeModule->Initialize())
    {
        std::cout << "Time Module failed to initialize!" << std::endl;
        return false;
    }

    m_windowModule = ModuleFactory::CreateWindowModule(this);
    if (!m_windowModule->Initialize())
    {
        std::cout << "Window Module failed to initialize!" << std::endl;
        return false;
    }

    std::cout << "Engine initialized." << std::endl;
    return true;
}

void Engine::Terminate()
{
    m_isRunning = false;

    m_game->Terminate();

    /*
        Terminate modules
    */

    m_windowModule->Terminate();
    m_timeModule->Terminate();

    std::cout << "Engine terminated." << std::endl;
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

void Engine::Update()
{
    m_windowModule->HandleWindowEvents();
    m_game->Update();
}

void Engine::Render()
{
    m_game->Render();
    m_windowModule->Display();
}

double Engine::GetDeltaTimeSeconds() const
{
    return m_deltaTimeSeconds;
}

}