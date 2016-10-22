/*
    GrimInputModule.hpp
    Engine

    Declan Hopkins
    9/9/2016

    The base Input Module.
*/

#pragma once

namespace grim::ui
{

class GrimInputModule : public IInputModule
{
public:
    GrimInputModule();
    ~GrimInputModule();

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        IInputModule Interface
    */

    virtual void Update() override;
    virtual void RegisterKeyPress(KeyScancode key) override;
    virtual void RegisterKeyRelease(KeyScancode key) override;
    virtual void RegisterMousePress(MouseButton button) override;
    virtual void RegisterMouseRelease(MouseButton button) override;
    virtual bool IsKeyHeld(KeyScancode key) const override;
    virtual bool IsKeyPressed(KeyScancode key) const override;
    virtual bool IsKeyReleased(KeyScancode key) const override;

private:
    bool m_heldKeys[static_cast<uint16_t>(KeyScancode::TotalKeys)];
    bool m_pressedKeys[static_cast<uint16_t>(KeyScancode::TotalKeys)];
    bool m_releasedKeys[static_cast<uint16_t>(KeyScancode::TotalKeys)];
    bool m_pressedMouseButtons[static_cast<uint16_t>(MouseButton::TotalButtons)];
    bool m_releasedMouseButtons[static_cast<uint16_t>(MouseButton::TotalButtons)];
};

}