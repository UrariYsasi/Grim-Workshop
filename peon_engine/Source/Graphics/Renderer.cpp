#include "PCH.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

namespace grim
{

namespace graphics
{

Renderer::Renderer()
{
    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default clear color
    SetClearColor(grim::graphics::Color(0.2f, 0.2f, 0.2f));
}

Renderer::~Renderer()
{
}

void Renderer::SetClearColor(const grim::graphics::Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::SetActiveCamera(graphics::Camera* camera)
{
    m_activeCamera = camera;
}

graphics::Camera* Renderer::GetActiveCamera()
{
    return m_activeCamera;
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}

}