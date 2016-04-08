#include "PCH.hpp"
#include "OpenGLRenderer.hpp"

namespace grim
{

namespace graphics
{

OpenGLRenderer::OpenGLRenderer()
{
    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default clear color
    SetClearColor(Color(0.2f, 0.2f, 0.2f));
}

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::SetClearColor(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRenderer::SetActiveCamera(Camera* camera)
{
    m_activeCamera = camera;
}

Camera* OpenGLRenderer::GetActiveCamera()
{
    return m_activeCamera;
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}

}