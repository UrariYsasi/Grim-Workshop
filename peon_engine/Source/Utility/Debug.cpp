#include "PCH.hpp"
#include "Debug.hpp"

namespace grim
{

namespace utility
{

uint8_t Debug::m_flags = 0;

/*
    Send some stuff to the debug log, if debugging is enabled.
*/
void Debug::Log(const char* format, ...)
{
    if (!IsFlagEnabled(LOGGING))
    {
        return;
    }

    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    std::vsnprintf(buffer, BUFFER_SIZE, format, args);
    va_end(args);
    std::cout << buffer << std::endl;
}

/*
    Send some stuff to the debug log, even if debugging is disabled.
*/
void Debug::LogError(const char* format, ...)
{
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    std::vsnprintf(buffer, BUFFER_SIZE, format, args);
    va_end(args);
    std::cout << buffer << std::endl;
}

void Debug::EnableFlag(uint8_t flag)
{
    m_flags |= flag;
}

void Debug::DisableFlag(uint8_t flag)
{
    m_flags &= ~flag;
}

void Debug::ToggleFlag(uint8_t flag)
{
    m_flags ^= flag;
}

bool Debug::IsFlagEnabled(uint8_t flag)
{
    if (m_flags & flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

}

}