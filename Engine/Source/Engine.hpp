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

        This frees all Engine resources. It should ONLY be called after the Engine loop has stopped!
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

    ITimeModule* GetTimeModule() const;
    IFileModule* GetFileModule() const;
    IWindowModule* GetWindowModule() const;
    IRendererModule* GetRendererModule() const;
    IAssetModule* GetAssetModule() const;

private:
    bool m_isRunning;
    IGame* m_game;
    double m_deltaTimeSeconds;

    /*
        Engine Modules
    */

    std::unique_ptr<ITimeModule> m_timeModule;
    std::unique_ptr<IFileModule> m_fileModule;
    std::unique_ptr<IWindowModule> m_windowModule;
    std::unique_ptr<IRendererModule> m_rendererModule;
    std::unique_ptr<IAssetModule> m_assetModule;
};

}