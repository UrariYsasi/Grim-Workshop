#pragma once

class Debug
{
public:
    static void Log(const char* format, ...);
    static void LogError(const char* format, ...);
    static void Enable();
    static void Disable();
    static bool IsEnabled();

private:
    static bool m_isEnabled;
};