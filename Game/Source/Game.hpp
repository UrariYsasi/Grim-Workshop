/*
    Game.hpp
    Peon Game

    Declan Hopkins
    8/1/2016
*/

#pragma once

class Game : grim::IGame
{
public:
    Game();

    /*
        Initialize the Game.

        Return: Success boolean.
    */
    bool Initialize();

    /*
        Run the Game.
    */
    void Run();

    /*
        IGame Interface
    */

    virtual void Terminate() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    grim::Engine m_engine;
};