#pragma once

namespace grim
{

namespace graphics
{

class IRenderer
{
public:
    virtual bool Initialize() = 0;
    virtual void Terminate() = 0;
    virtual void Clear() = 0;
    virtual void Render() = 0;
    virtual void Submit(const RenderCommand& command) = 0;
    virtual void SetLayerCamera(const uint8_t layer, Camera* camera) = 0;

    virtual std::unique_ptr<assets::Texture> CreateTexture(std::string const& id, uint32_t const& width, uint32_t const& height, unsigned char const*) const = 0;

    virtual void SetClearColor(const Color& color) = 0;
    virtual void SetActiveCamera(Camera* camera) = 0;
    virtual Camera* GetActiveCamera() = 0;
};

}

}