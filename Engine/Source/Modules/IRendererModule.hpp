/*
    IRendererModule.hpp
    Peon Engine

    Declan Hopkins
    8/5/2016

    An Engine module responsible for interfacing with the lower level graphics API to render the game.
*/

#pragma once

namespace grim
{

class IRendererModule : public IModule
{
public:
    /*
        Clear the render buffers.

        This prepares the context for a new render, and is the first step in the render process.
    */
    virtual void Clear() = 0;

    /*
        Render the frame.

        This processes and renders all submitted commands.
    */
    virtual void Render() = 0;

    /*
        Submit a command.

        The submitted command will be sorted appropriately and rendered at the end of the frame.
    */
    virtual void Submit() = 0;
};

}