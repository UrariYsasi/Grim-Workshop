#pragma once

namespace grim
{

class Engine
{
public:
    Engine();
    ~Engine();

    /*
        Initialize the the Engine to prepare it to run.
    */

    uint8_t Initialize();

    grim::graphics::IWindow* GetWindow();
    grim::graphics::IRenderer* GetRenderer();
    grim::audio::IAudio* GetAudio();
    grim::ui::IInput* GetInput();
    grim::ui::IUserInterface* GetUI();

    uint32_t GetTime();

protected:

    /*
        Alert the Engine that it should stop running that and the application should quit.
    */

    void Terminate();

    /*
        Run the Engine loop.

        The loop processes input, updates logic, and then renders. This is essentially
        the "heartbeat" of the Engine.
    */

    void Run();

    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

protected:
    bool m_isRunning;
    uint32_t m_frameCount;
    uint16_t m_frameRate;
    uint32_t m_gameStartTime;

private:

    /*
        Services
    */

    std::unique_ptr<grim::graphics::IWindow> m_window;
    std::unique_ptr<grim::graphics::IRenderer> m_renderer;
    std::unique_ptr<grim::audio::IAudio> m_audio;
    std::unique_ptr<grim::ui::IInput> m_input;
    std::unique_ptr<grim::ui::IUserInterface> m_ui;
};

}