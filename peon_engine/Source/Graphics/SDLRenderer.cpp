#include "PCH.hpp"
#include "SDLRenderer.hpp"

namespace grim
{

namespace graphics
{

SDLRenderer::SDLRenderer()
{
    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default clear color
    SetClearColor(Color(0.2f, 0.2f, 0.2f));
}

SDLRenderer::~SDLRenderer()
{
}

void SDLRenderer::SetClearColor(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void SDLRenderer::SetActiveCamera(Camera* camera)
{
    m_activeCamera = camera;
}

Camera* SDLRenderer::GetActiveCamera()
{
    return m_activeCamera;
}

void SDLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}

}