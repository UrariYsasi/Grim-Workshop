#include "PCH.hpp"
#include "Debug.hpp"

bool Debug::m_isEnabled = true;

/*
    Send some stuff to the debug log, if debugging is enabled.
*/
void Debug::Log(const char* format, ...)
{
    if (!m_isEnabled)
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

void Debug::Enable()
{
    Debug::m_isEnabled = true;
}

void Debug::Disable()
{
    Debug::m_isEnabled = false;
}

bool Debug::IsEnabled()
{
    return Debug::m_isEnabled;
}