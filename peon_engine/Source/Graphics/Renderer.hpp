#pragma once

namespace grim
{

namespace graphics
{

class Camera;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void SetClearColor(const grim::graphics::Color& color);
    void SetActiveCamera(graphics::Camera* camera);
    graphics::Camera* GetActiveCamera();

    void Clear();

private:
    graphics::Camera* m_activeCamera;
};

}

}