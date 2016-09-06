/*
    Logger.cpp
    Engine

    Declan Hopkins
    9/6/2016
*/

#include "PCH.hpp"
#include "Logger.hpp"

namespace grim
{

Logger::Logger() :
    logStream()
{
}

Logger::~Logger()
{
    logStream << std::endl;

    std::cout << logStream.str();
    std::ofstream outputStream(LOG_FILE_NAME, std::ofstream::app);
    outputStream << logStream.str();
    outputStream.close();
}

void Logger::Clear()
{
    std::ofstream outputStream(LOG_FILE_NAME, std::ofstream::trunc);
    outputStream.close();
}

std::ostringstream& Logger::Get(LogLevel level)
{
    logStream << "[" << LogLevelToString(level) << "] ";

    return logStream;
}

std::string Logger::LogLevelToString(LogLevel level)
{
    if (level == LogLevel::Info)
    {
        return "Info";
    }
    else if (level == LogLevel::Warning)
    {
        return "Warning";
    }
    else if (level == LogLevel::Error)
    {
        return "Error";
    }

    return "Log";
}

}