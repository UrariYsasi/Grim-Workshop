#pragma once

class Window
{
    public:
        Window(const int& width, const int& height, const std::string& title);
        ~Window();

        SDL_Window* GetSDLWindow() const;
        void SetSize(const glm::vec2& size);
        glm::vec2 GetSize() const;
        void SetTitle(const std::string& title);
        std::string GetTitle() const;

        int Initialize();

        /*
            Update the Window with the OpenGL context.
        */
        void SwapWindow();

    private:
        SDL_Window* m_SDLWindow;
        SDL_GLContext m_glContext;
        glm::vec2 m_size;
        std::string m_title;
};
