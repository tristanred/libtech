#include "libtech/filelogger.h"


#include <string>
#include <cstring>

void RegisterLogger(FileLogger* logger)
{
    if(_globalLogger != NULL)
    {
        delete(_globalLogger);
    }

    _globalLogger = logger;
}

void LogMessage(const char* message)
{
    if(_globalLogger != NULL)
    {
        _globalLogger->LogMessage(message);
    }
}

void LogWarning(const char* message)
{
    if(_globalLogger != NULL)
    {
        _globalLogger->LogWarning(message);
    }
}

void LogError(const char* message)
{
    if(_globalLogger != NULL)
    {
        _globalLogger->LogError(message);
    }
}


FileLogger::FileLogger()
{
    enabled = true;
    currentLevel = LOG_ALL;
}

FileLogger::~FileLogger()
{
    if(logFile != NULL)
    {
        fclose(logFile);
    }
}

void FileLogger::Log(enum LOG_LEVEL level, const char* message)
{
    if(enabled && logFile != NULL)
    {
        std::string msg;
        msg.append(levelNames[level]);
        msg.append(" ");
        msg.append(message);

        int result = fputs(msg.c_str(), logFile);

        if(result == EOF)
        {
            // Error
        }
    }
}

void FileLogger::Open(const char* filepath)
{
    logFile = fopen(filepath, "w");

    if(logFile != NULL)
    {

    }
}

void FileLogger::Close()
{
    if(logFile != NULL)
    {
        fclose(logFile);
        logFile = NULL;
    }
}

void FileLogger::LogMessage(const char* message)
{
    this->Log(LOG_MSG, message);
}

void FileLogger::LogWarning(const char* message)
{
    this->Log(LOG_WARN, message);
}

void FileLogger::LogError(const char* message)
{
    this->Log(LOG_ERROR, message);
}
