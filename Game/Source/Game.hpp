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
        Terminate the Game.
    */
    virtual void Terminate() override;

    /*
        Run the Game.
    */
    void Run();

    virtual void Update() override;
    virtual void Render() override;

private:
    grim::Engine m_engine;
};