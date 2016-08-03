/*
    Engine.hpp
    Peon Engine

    Declan Hopkins
    8/1/2016
*/

#pragma once

namespace grim
{

class Engine
{
public:
    Engine(IGame* const game);

    /*
        Initialize the Engine and Engine Modules.

        Return: Success boolean.
    */
    bool Initialize();

    /*
        Terminate the Engine and Engine Modules.
    */
    void Terminate();

    /*
        Run the Engine and Engine Modules.
    */
    void Run();

    void Update();
    void Render();

private:
    bool m_isRunning;
    IGame* m_game;

    /*
        Engine Modules
    */

    std::unique_ptr<IWindowModule> m_windowModule;
};

}