#pragma once
// Tyren Review: Never include PCH in headers
#include "../PCH.hpp"

class Window
{
    public:
        Window(const int& width, const int& height, const std::string& title);
        ~Window();

        SDL_Window* GetSDLWindow() const;
        int GetWidth() const;
        void SetWidth(const int& width);
        int GetHeight() const;
        void SetHeight(const int& height);
        std::string GetTitle() const;
        void SetTitle(const std::string& title);

    private:
        SDL_Window* m_SDLWindow;
        int m_width;
        int m_height;
        std::string m_title;
};
