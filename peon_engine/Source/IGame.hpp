/*
    IGame.hpp
    Engine

    Declan Hopkins
    9/1/2016

    This interface is implemented by the base game class, allowing the game to hook into the
    Engine loop. The Engine will not run without a game that implements this.
*/

#pragma once

namespace grim
{

class IGame
{
public:
    virtual void Update() = 0;
    virtual void Render() = 0;
};

}