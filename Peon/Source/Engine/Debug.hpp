#pragma once

class Debug
{
public:
    static void Log(const std::string format, ...);
    static void LogError(const std::string format, ...);
    static void Enable();
    static void Disable();
    static bool IsEnabled();

private:
    static bool m_isEnabled;
};