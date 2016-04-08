#pragma once

namespace grim
{

namespace graphics
{

class IRenderer
{
public:
    virtual void SetClearColor(const Color& color) = 0;
    virtual void SetActiveCamera(Camera* camera) = 0;
    virtual Camera* GetActiveCamera() = 0;

    virtual void Clear() = 0;
};

}

}