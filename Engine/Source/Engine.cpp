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
}

}