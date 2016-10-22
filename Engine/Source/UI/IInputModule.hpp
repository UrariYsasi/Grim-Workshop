/*
    IInputModule.hpp
    Engine

    Declan Hopkins
    8/2/2016

    An Engine Module responsible for receiving and storing user input from the Window Module.
*/

#pragma once

namespace grim::ui
{

class IInputModule : public IModule
{
public:
    virtual void Update() = 0;

    virtual void RegisterKeyPress(KeyScancode key) = 0;
    virtual void RegisterKeyRelease(KeyScancode key) = 0;

    virtual void RegisterMousePress(MouseButton button) = 0;
    virtual void RegisterMouseRelease(MouseButton button) = 0;

    virtual bool IsKeyHeld(KeyScancode key) const = 0;
    virtual bool IsKeyPressed(KeyScancode key) const  = 0;
    virtual bool IsKeyReleased(KeyScancode key) const  = 0;
};

}