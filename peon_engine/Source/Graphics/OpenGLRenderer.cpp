#include "PCH.hpp"
#include "OpenGLRenderer.hpp"

namespace grim
{

namespace graphics
{

OpenGLRenderer::OpenGLRenderer()
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}

bool OpenGLRenderer::Initialize()
{
    // Initialize GL3W
    if (gl3wInit())
    {
        grim::utility::Debug::LogError("GL3W failed to initialize!");
        return false;
    }

    if (!gl3wIsSupported(3, 2))
    {
        grim::utility::Debug::LogError("OpenGL 3.2 not supported!");
        return false;
    }

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default clear color
    SetClearColor(Color(0.2f, 0.2f, 0.2f));

    grim::utility::Debug::LogError("Renderer module OpenGLRenderer initialized.");
    grim::utility::Debug::Log("    - OpenGL version %s", glGetString(GL_VERSION));
    grim::utility::Debug::Log("    - GLSL version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    return true;
}

void OpenGLRenderer::Terminate()
{
    grim::utility::Debug::LogError("Renderer module OpenGLRenderer terminated.");
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::Render()
{
    // TODO: Sort m_renderQueue!

    uint32_t renderCommandCount = 0;
    while (!m_renderQueue.empty())
    {
        RenderCommand command = m_renderQueue.back();
        m_renderQueue.pop_back();

        renderCommandCount++;
    }

    grim::utility::Debug::Log("Rendered %d commands", renderCommandCount);
}

void OpenGLRenderer::Submit(const RenderCommand& command)
{
    m_renderQueue.push_back(command);
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

}

}