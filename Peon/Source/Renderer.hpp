#pragma once
#include "PCH.hpp"
#include "Window.hpp"

class Renderer
{
    public:
        Renderer(const Window* window);
        ~Renderer();

        SDL_Renderer* GetSDLRenderer() const;
        void SetDrawColor(const SDL_Color& drawColor);

        void Clear();
        void Present();

    private:
        SDL_Renderer* m_SDLRenderer;
};

inline SDL_Renderer* Renderer::GetSDLRenderer() const
{
    return m_SDLRenderer;
}

inline void Renderer::SetDrawColor(const SDL_Color& drawColor)
{
    SDL_SetRenderDrawColor(m_SDLRenderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
}