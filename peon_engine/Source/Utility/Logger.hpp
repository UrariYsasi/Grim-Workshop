/*
    Logger.hpp
    Engine

    Declan Hopkins
    9/6/2016

    A utility for logging info, warnings, and errors to the log file. The log file should be cleared
    when the program starts.
*/

#pragma once

#define LOG() grim::Logger().Get(grim::LogLevel::Info)
#define LOG_WARNING() grim::Logger().Get(grim::LogLevel::Warning)
#define LOG_ERROR() grim::Logger().Get(grim::LogLevel::Error)

namespace grim
{

enum class LogLevel { Info, Warning, Error };

class Logger
{
public:
    Logger();
    ~Logger();

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