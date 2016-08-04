/*
    Log.hpp
    Peon Engine

    Declan Hopkins
    8/3/2016

    A utility for logging info, warnings, and errors to the log file. The log file should be cleared
    when the program starts.
*/

#pragma once

#define LOG() grim::Log().Get(grim::LogLevel::Info)
#define LOG_WARNING() grim::Log().Get(grim::LogLevel::Warning)
#define LOG_ERROR() grim::Log().Get(grim::LogLevel::Error)

namespace grim
{

enum class LogLevel { Info, Warning, Error };

class Log
{
public:
    Log();
    ~Log();

    /*
        Clear the log file.
    */
    static void Clear();

    std::ostringstream& Get(LogLevel level = LogLevel::Info);

private:
    std::string LogLevelToString(LogLevel level);

private:
    std::ostringstream logStream;
};

}