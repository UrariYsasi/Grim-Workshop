#include "../PCH.hpp"
#include "Timer.hpp"

Timer::Timer() :
    m_startTime(0),
    m_pausedTime(0),
    m_isStarted(false),
    m_isPaused(false)
{
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
    // Tyren Review: Maybe add a comment to explain in english goal of this
    if (m_isStarted && !m_isPaused)
    {
        m_isPaused = true;
        m_pausedTime = SDL_GetTicks() - m_startTime;
        m_startTime = 0;
    }
}

// Tyren Review: UnCool, this is UnSpecial and UnRight... Unpause? :)
void Timer::UnPause()
{
    // Tyren Review: Maybe add a comment to explain in english goal of this
    if (m_isStarted && m_isPaused)
    {
        m_isPaused = false;
        m_startTime = SDL_GetTicks() - m_pausedTime;
        m_pausedTime = 0;
    }
}

double Timer::GetTime()
{
    // Tyren Review: Is this necessary? Can't you just return the correct value below
    // And 0 otherwise?
    double time = 0;

    if (m_isStarted)
    {
        if (m_isPaused)
        {
            time = m_pausedTime;
        }
        else
        {
            time = SDL_GetTicks() - m_startTime;
        }
    }

    return time;
}

bool Timer::IsStarted()
{
    return m_isStarted;
}

bool Timer::IsPaused()
{
    return m_isPaused;
}
