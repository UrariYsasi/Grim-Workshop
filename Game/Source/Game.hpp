/*
    Game.hpp
    Peon Game

    Declan Hopkins
    8/1/2016
*/

#pragma once

class Game : public grim::IGame
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

        Frees any resources owned by the Game. This function is called before the Engine
        terminates.
    */
    void Terminate();

    /*
        Start running the Game.
    */
    void Run();

    /*
        IGame Interface
    */

    virtual void Update() override;
    virtual void Render() override;

private:
    std::unique_ptr<grim::Engine> m_engine;
};