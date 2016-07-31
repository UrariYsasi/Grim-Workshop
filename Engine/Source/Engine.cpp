#include "PCH.hpp"
#include "Engine.hpp"

Engine::Engine()
{
    std::cout << "Engine init" << std::endl;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "failed!" << std::endl;
    }
}