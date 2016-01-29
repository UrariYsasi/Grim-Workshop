#include "PCH.hpp"
#include "Renderer.hpp"
#include "Window.hpp"

Renderer::Renderer(const Window* window)
{
    m_SDLRenderer = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_SDLRenderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL error: " << SDL_GetError() << std::endl;
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_SDLRenderer);
}

SDL_Renderer* Renderer::GetSDLRenderer() const
{
    return m_SDLRenderer;
}

void Renderer::SetDrawColor(const SDL_Color& drawColor)
{
    SDL_SetRenderDrawColor(m_SDLRenderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
}

void Renderer::Clear()
{
    SDL_RenderClear(m_SDLRenderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(m_SDLRenderer);
}
