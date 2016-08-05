/*
    OpenGLWindowModule.hpp
    Peon Engine

    Declan Hopkins
    8/2/2016

    A Window Module that supports and displays a window with an OpenGL context. Using this Module 
    requires that the Renderer Module is using the OpenGL API.
*/

#pragma once

namespace grim
{

class Engine;

class OpenGLWindowModule : public IWindowModule
{
public:
    OpenGLWindowModule(Engine* const engine, const std::string& title, const uint16_t& width, const uint16_t& height, const bool& isFullscreen);
    ~OpenGLWindowModule();

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        IWindowModule Interface
    */
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
