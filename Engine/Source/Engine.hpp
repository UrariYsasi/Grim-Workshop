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

        This frees all Engine resources and should be called after the Engine loop has stopped.
    */
    void Terminate();

    /*
        Start running the Engine loop.
    */
    void Run();

    /*
        Stop running the Engine loop.
    */
    void Stop();

    void Update();
    void Render();

    /*
        Get the Engine delta time. 
        
        This is the time that it took to execute the last frame, and is used for framerate 
        independence.
    */
    double GetDeltaTimeSeconds() const;

private:
    bool m_isRunning;
    IGame* m_game;
    double m_deltaTimeSeconds;

    /*
        Engine Modules
    */

    std::unique_ptr<IWindowModule> m_windowModule;
    std::unique_ptr<ITimeModule> m_timeModule;
};

}