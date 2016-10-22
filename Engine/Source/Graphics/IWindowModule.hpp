/*
    IWindowModule.hpp
    Engine

    Declan Hopkins
    9/6/2016

    An Engine module responsible for the creation and management of the game window.
*/

#pragma once

namespace grim
{

namespace graphics
{

class IWindowModule : public IModule
{
public:
    /*
        Poll the OS for window events and handle them accordingly.
    */
    virtual void HandleWindowEvents() = 0;

    /*
        Swap the window buffers and display the current frame.
    */
    virtual void Display() = 0;

    virtual void SetSize(const glm::ivec2& size) = 0;
    virtual void SetTitle(const std::string& title) = 0;
    virtual glm::ivec2 GetSize() const = 0;
    virtual std::string GetTitle() const = 0;
};

}

}