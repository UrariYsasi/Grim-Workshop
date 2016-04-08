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

    virtual void SetClearColor(const Color& color);
    virtual void SetActiveCamera(Camera* camera);
    virtual Camera* GetActiveCamera();

    void Clear();

private:
    Camera* m_activeCamera;
};

}

}