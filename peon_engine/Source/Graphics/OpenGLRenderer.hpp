#pragma once

namespace grim
{

namespace graphics
{

class OpenGLRenderer : public IRenderer
{
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    virtual bool Initialize();
    virtual void Terminate();
    virtual void Clear();
    virtual void Render();

    virtual void SetClearColor(const Color& color);
    virtual void SetActiveCamera(Camera* camera);
    virtual Camera* GetActiveCamera();

private:
    Camera* m_activeCamera;
};

}

}