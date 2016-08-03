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
    m_windowModule(nullptr)
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

    std::cout << "Engine terminated." << std::endl;
}

void Engine::Run()
{
    m_isRunning = true;

    /*
        Engine loop
    */

    // TODO make an actual Time module and move some nasty time stuff there
    float frameStartTimeSeconds = 0.0;
    float frameEndTimeSeconds = 0.0;
    float deltaTimeSeconds = 0.0f;

    while (m_isRunning)
    {
        deltaTimeSeconds = frameEndTimeSeconds - frameStartTimeSeconds;
        frameStartTimeSeconds = static_cast<float>(SDL_GetTicks() / 1000.0f);
        
        // TODO move deltaTimeSeconds to time module

        Update();
        Render();

        frameEndTimeSeconds = static_cast<float>(SDL_GetTicks() / 1000.0f);
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

}