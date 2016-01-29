#pragma once
// Tyren Review: Never include PCH in headers
#include "../PCH.hpp"

// Tyren Review: Not necessary, just forward decalre and include in CPP
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
