#pragma once

class Game;

namespace grim
{

namespace graphics
{

class Window;
class Camera;

class Renderer
{
public:
    Renderer(Game* game, const grim::graphics::Window* window);
    ~Renderer();

    void SetClearColor(const grim::graphics::Color& color);
    void SetActiveCamera(graphics::Camera* camera);
    graphics::Camera* GetActiveCamera();

    void Clear();

    void RenderTexture(const std::string& id, const int& x, const int& y, const int& width, const int& height);
    void RenderSprite(const std::string& id, const int& col, const int& row, const int& x, const int& y, const int& width, const int& height);
    void RenderText(const std::string& id, const int& x, const int& y, const std::string& text, const SDL_Color& color = { 0, 0, 0, 255 });
    void RenderOutlineRect(const grim::graphics::Rect& rect, const SDL_Color& color = { 0, 0, 0, 255 });
    void RenderFillRect(const grim::graphics::Rect& rect, const SDL_Color& color = { 0, 0, 0, 255 });

private:
    Game* m_game;
    graphics::Camera* m_activeCamera;
};

}

}