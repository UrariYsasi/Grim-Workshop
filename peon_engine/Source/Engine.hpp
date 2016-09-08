/*
    Engine.hpp
    Engine

    Declan Hopkins
    8/31/2016
*/

#pragma once

namespace grim
{

class Engine
{
public:
    Engine(IGame* const game);
    ~Engine();

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

    grim::graphics::IRenderer* GetRenderer();
    grim::audio::IAudio* GetAudio();
    grim::ui::IInput* GetInput();
    grim::ui::IUserInterface* GetUI();

    graphics::IWindowModule* GetWindowModule();
    utility::ITimeModule* GetTimeModule();
    platform::IFileModule* GetFileModule();

private:
    bool m_isRunning;
    IGame* m_game;
    double m_deltaTimeSeconds;

public:
    uint32_t m_frameCount;
    uint16_t m_frameRate;

private:

    /*
        Modules
    */

    std::unique_ptr<utility::ITimeModule> m_timeModule;
    std::unique_ptr<graphics::IWindowModule> m_windowModule;
    std::unique_ptr<platform::IFileModule> m_fileModule;

    // LEGACY
    std::unique_ptr<graphics::IRenderer> m_renderer;
    std::unique_ptr<audio::IAudio> m_audio;
    std::unique_ptr<ui::IInput> m_input;
    std::unique_ptr<ui::IUserInterface> m_ui;
};

}