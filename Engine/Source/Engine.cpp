#include "PCH.hpp"
#include "Engine.hpp"

namespace grim
{

Engine::Engine() :
    m_isRunning(false)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "failed!" << std::endl;
    }
}

bool Engine::Initialize()
{
    /*
        Initialize modules
    */

    std::cout << "Engine initialized." << std::endl;

    return true;
}

void Engine::Terminate()
{
    /*
        Terminate modules
    */
}

void Engine::Run()
{
    m_isRunning = true;

    /*
        Engine loop
    */

    // TODO make an actual Time module
    float frameStartTimeSeconds = 0.0;
    float frameEndTimeSeconds = 0.0;
    float deltaTimeSeconds = 0.0f;

    while (m_isRunning)
    {
        deltaTimeSeconds = frameEndTimeSeconds - frameStartTimeSeconds;
        frameStartTimeSeconds = static_cast<float>(SDL_GetTicks() / 1000.0f);
        
        Update(deltaTimeSeconds);
        Render();

        frameEndTimeSeconds = static_cast<float>(SDL_GetTicks() / 1000.0f);
    }
}

void Engine::Update(const float& deltaTimeSeconds)
{

}

void Engine::Render()
{

}

}