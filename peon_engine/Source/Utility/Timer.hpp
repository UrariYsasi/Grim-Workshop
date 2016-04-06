#pragma once

namespace grim
{

namespace utility
{

class Timer
{
public:
    Timer();

    double GetTime() const;
    bool IsStarted() const;
    bool IsPaused() const;

    void Start();
    void Stop();
    void Pause();
    void Resume();
private:
    double m_startTime;
    double m_pausedTime;
    bool m_isStarted;
    bool m_isPaused;
};

}

}