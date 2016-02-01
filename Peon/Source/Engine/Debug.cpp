#include "PCH.hpp"
#include "Debug.hpp"

bool Debug::m_isEnabled = true;

/*
    Send some stuff to the debug log, if debugging is enabled.
*/
void Debug::Log(const std::string format, ...)
{
    if (!m_isEnabled)
    {
        return;
    }

    va_list args;
    va_start(args, format);
    char buffer[1024];
    std::vsnprintf(buffer, (sizeof(buffer) / sizeof buffer[0]), format.c_str(), args);
    va_end(args);
    std::cout << buffer << std::endl;
}

/*
    Send some stuff to the debug log, even if debugging is disabled.
*/
void Debug::LogError(const std::string format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[1024];
    std::vsnprintf(buffer, (sizeof(buffer) / sizeof buffer[0]), format.c_str(), args);
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