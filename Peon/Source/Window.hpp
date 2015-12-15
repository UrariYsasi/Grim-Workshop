#pragma once
#include "PCH.hpp"

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

inline SDL_Window* Window::GetSDLWindow() const
{
    return m_SDLWindow;
}

inline int Window::GetWidth() const
{
    return m_width;
}

inline void Window::SetWidth(const int& width)
{
    m_width = width;
}

inline int Window::GetHeight() const
{
    return m_height;
}

inline void Window::SetHeight(const int& height)
{
    m_height = height;
}

inline std::string Window::GetTitle() const
{
    return m_title;
}

inline void Window::SetTitle(const std::string& title)
{
    m_title = title;
}