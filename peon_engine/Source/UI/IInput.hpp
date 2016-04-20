#pragma once

namespace grim
{

namespace ui
{

class IInput
{
public:
    virtual bool Initialize() = 0;
    virtual void Terminate() = 0;
    virtual void Update() = 0;

    virtual void SetQuitCallback(std::function<void()> quitCallback) = 0;
    virtual bool GetKey(int key) = 0;
    virtual bool GetKeyPress(int key) = 0;
    virtual bool GetKeyRelease(int key) = 0;
    virtual bool GetMouseButton(int button) = 0;
    virtual bool GetMouseButtonPress(int button) = 0;
    virtual bool GetMouseButtonRelease(int button) = 0;
    virtual glm::vec2 GetMousePosition() const = 0;
};

}

}