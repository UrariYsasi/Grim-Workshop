#include "PCH.hpp"
#include "OpenGLRenderer.hpp"

namespace grim
{

namespace graphics
{

OpenGLRenderer::OpenGLRenderer()
{
    // Initialize GL3W
    if (gl3wInit())
    {
        grim::utility::Debug::LogError("GL3W failed to initialize!");
    }

    if (!gl3wIsSupported(3, 2))
    {
        grim::utility::Debug::LogError("OpenGL 3.2 not supported!");
    }

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