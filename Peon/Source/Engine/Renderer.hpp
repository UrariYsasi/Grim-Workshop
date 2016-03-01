#pragma once

class Window;
class Game;

namespace grim
{

class Camera;

class Renderer
{
public:
    Renderer(Game* game, const Window* window);
    ~Renderer();

    void SetClearColor(const grim::Color& color);
    void SetActiveCamera(grim::Camera* camera);
    grim::Camera* GetActiveCamera();

    void Clear();

    void RenderTexture(const std::string& id, const int& x, const int& y, const int& width, const int& height);
    void RenderSprite(const std::string& id, const int& col, const int& row, const int& x, const int& y, const int& width, const int& height);
    void RenderText(const std::string& id, const int& x, const int& y, const std::string& text, const SDL_Color& color = { 0, 0, 0, 255 });
    void RenderOutlineRect(const Rect& rect, const SDL_Color& color = { 0, 0, 0, 255 });
    void RenderFillRect(const Rect& rect, const SDL_Color& color = { 0, 0, 0, 255 });

private:
    Game* m_game;
    Camera* m_activeCamera;
};

}
