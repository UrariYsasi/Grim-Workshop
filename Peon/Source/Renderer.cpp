#include "Renderer.hpp"

Renderer::Renderer(const Window* window)
{
    m_SDLRenderer = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);
    if (m_SDLRenderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL error: " << SDL_GetError() << std::endl;
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_SDLRenderer);
}

void Renderer::Clear()
{
    SDL_RenderClear(m_SDLRenderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(m_SDLRenderer);
}