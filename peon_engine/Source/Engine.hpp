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
        Initialize the the Engine and prepare it to run.
    */

    bool Initialize();

    void SetTimeScale(float scale);
    grim::graphics::IWindow* GetWindow();
    grim::graphics::IRenderer* GetRenderer();
    grim::audio::IAudio* GetAudio();
    grim::ui::IInput* GetInput();
    grim::ui::IUserInterface* GetUI();
    uint32_t GetTime();

    /*
        Alert the Engine that it should stop running that and the application should quit.
    */

    virtual void Terminate();

    /*
        Run the Engine loop.

        The loop processes input, updates logic, and then renders. This is essentially
        the "heartbeat" of the Engine.
    */

    virtual void Run();

    virtual void Update(float deltaTime);
    virtual void Render();

public:
    IGame* m_game;
    bool m_isRunning;
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