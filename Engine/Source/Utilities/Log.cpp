/*
    Log.cpp
    Peon Engine

    Declan Hopkins
    8/3/2016
*/

#include "PCH.hpp"
#include "Log.hpp"

namespace grim
{

Log::Log() :
    logStream()
{
}

Log::~Log()
{
    logStream << std::endl;

    std::cout << logStream.str();
    std::ofstream outputStream(LOG_FILE_NAME, std::ofstream::app);
    outputStream << logStream.str();
    outputStream.close();
}

void Log::Clear()
{
    std::ofstream outputStream(LOG_FILE_NAME, std::ofstream::trunc);
    outputStream.close();
}

std::ostringstream& Log::Get(LogLevel level)
{
    logStream << "[" << LogLevelToString(level) << "] ";

    return logStream;
}

std::string Log::LogLevelToString(LogLevel level)
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