#pragma once

namespace grim
{

namespace graphics
{

class SDLRenderer : public IRenderer
{
public:
    SDLRenderer();
    ~SDLRenderer();

    virtual void SetClearColor(const Color& color);
    virtual void SetActiveCamera(Camera* camera);
    virtual Camera* GetActiveCamera();

    void Clear();

private:
    Camera* m_activeCamera;
};

}

}