/*
    IGame.hpp
    Peon Engine

    Declan Hopkins
    8/2/2016

    This interface is implemented by the base game class, allowing the game to hook into the
    Engine loop and be managed by the engine. The Engine will not run without a game that implements this.
*/

#pragma once

namespace grim
{

class IGame
{
public:
    virtual void Terminate() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
};

}