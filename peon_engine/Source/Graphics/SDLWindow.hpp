#pragma once

namespace grim
{

namespace graphics
{

class SDLWindow : public IWindow
{
public:
    SDLWindow(const uint16_t& width, const uint16_t& height, const std::string& title, const bool isFullScreen);
    ~SDLWindow();

    virtual SDL_Window* GetSDLWindow() const;
    virtual void SetSize(const glm::vec2& size);
    virtual glm::vec2 GetSize() const;
    virtual void SetTitle(const std::string& title);
    virtual std::string GetTitle() const;

    virtual bool Initialize();
    virtual void SwapWindow();

private:
    SDL_Window* m_SDLWindow;
    SDL_GLContext m_glContext;
    glm::vec2 m_size;
    std::string m_title;
    bool m_isFullScreen;
};

}

}