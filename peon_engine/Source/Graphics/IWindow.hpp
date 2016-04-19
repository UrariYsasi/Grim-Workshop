#pragma once

namespace grim
{

namespace graphics
{

class IWindow
{
public:
    virtual void SetSize(const glm::vec2& size) = 0;
    virtual glm::vec2 GetSize() const = 0;
    virtual void SetTitle(const std::string& title) = 0;
    virtual std::string GetTitle() const = 0;

    virtual bool Initialize() = 0;
    virtual void SwapWindow() = 0;
};

}

}