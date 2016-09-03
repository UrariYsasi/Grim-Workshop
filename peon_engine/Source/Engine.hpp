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

    void SetTimeScale(float scale);
    grim::graphics::IWindow* GetWindow();
    grim::graphics::IRenderer* GetRenderer();
    grim::audio::IAudio* GetAudio();
    grim::ui::IInput* GetInput();
    grim::ui::IUserInterface* GetUI();
    uint32_t GetTime();

private:
    bool m_isRunning;
    IGame* m_game;

public:
    uint32_t m_frameCount;
    uint16_t m_frameRate;
    uint32_t m_gameStartTime;
    float m_timeScale;

private:

    /*
        Modules
    */

    std::unique_ptr<grim::graphics::IWindow> m_window;
    std::unique_ptr<grim::graphics::IRenderer> m_renderer;
    std::unique_ptr<grim::audio::IAudio> m_audio;
    std::unique_ptr<grim::ui::IInput> m_input;
    std::unique_ptr<grim::ui::IUserInterface> m_ui;
};

}