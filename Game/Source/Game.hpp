#pragma once

class Game
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
    void Terminate();

    /*
        Run the Game.
    */
    void Run();

private:
    grim::Engine m_engine;
};