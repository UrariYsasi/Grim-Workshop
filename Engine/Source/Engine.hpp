#pragma once

namespace grim
{

class Engine
{
public:
    Engine();

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

    void Update(const float& deltaTimeSeconds);
    void Render();

private:
    bool m_isRunning;
};

}