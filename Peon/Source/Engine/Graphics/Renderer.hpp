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

private:
    Game* m_game;
    graphics::Camera* m_activeCamera;
};

}

}