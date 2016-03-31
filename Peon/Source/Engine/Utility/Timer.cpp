#include "PCH.hpp"
#include "Timer.hpp"

namespace grim
{

namespace utility
{

Timer::Timer() :
    m_startTime(0.0),
    m_pausedTime(0.0),
    m_isStarted(false),
    m_isPaused(false)
{
}

double Timer::GetTime() const
{
    if (m_isStarted)
    {
        if (m_isPaused)
        {
            return m_pausedTime;
        }
        else
        {
            return SDL_GetTicks() - m_startTime;
        }
    }

    return 0;
}

bool Timer::IsStarted() const
{
    return m_isStarted;
}

bool Timer::IsPaused() const
{
    return m_isPaused;
}

void Timer::Start()
{
    m_isStarted = true;
    m_isPaused = false;
    m_startTime = SDL_GetTicks();
    m_pausedTime = 0;
}

void Timer::Stop()
{
    m_isStarted = false;
    m_isPaused = false;
    m_startTime = 0;
    m_pausedTime = 0;
}

void Timer::Pause()
{
    // If the timer is started, and isn't paused
    if (m_isStarted && !m_isPaused)
    {
        // Puase the timer, set the paused time to the current time, and reset the start time.
        m_isPaused = true;
        m_pausedTime = SDL_GetTicks() - m_startTime;
        m_startTime = 0;
    }
}

void Timer::Resume()
{
    // If the timer is started, and is paused
    if (m_isStarted && m_isPaused)
    {
        // Resume the timer, set our new start time, and reset the paused time.
        m_isPaused = false;
        m_startTime = SDL_GetTicks() - m_pausedTime;
        m_pausedTime = 0;
    }
}

}

}