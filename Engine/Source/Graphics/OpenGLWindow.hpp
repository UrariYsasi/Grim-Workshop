/*
    OpenGLWindow.hpp
    Peon Engine

    Declan Hopkins
    8/2/2016

    A Window Module that supports and displays a window with an OpenGL context.
*/

#pragma once

namespace grim
{

class Engine;

class OpenGLWindow : public IWindowModule
{
public:
    OpenGLWindow(Engine* const engine, const std::string& title, const uint16_t& width, const uint16_t& height, const bool& isFullscreen);
    ~OpenGLWindow();

    virtual bool Initialize() override;
    virtual void Terminate() override;
    virtual void HandleWindowEvents() override;
    virtual void Display() override;

    virtual void SetSize(const glm::ivec2& size) override;
    virtual void SetTitle(const std::string& title) override;
    virtual glm::ivec2 GetSize() const override;
    virtual std::string GetTitle() const override;

private:
    Engine* m_engine;
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    std::string m_title;
    glm::ivec2 m_size;
    bool m_isFullscreen;
};

}
