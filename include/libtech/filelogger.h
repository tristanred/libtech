#pragma once

#include "libtech.h"

#include <cstdarg>
#include <cstdio>
using namespace std;

enum LOG_LEVEL{
    LOG_TRACE,
    LOG_MSG,
    LOG_WARN,
    LOG_ERROR,
    LOG_LEVELCOUNT
};

class FileLogger;
LIBTECH_API void RegisterLogger(FileLogger* logger);
LIBTECH_API void LogTrace(const char* message, ...);
LIBTECH_API void LogMessage(const char* message, ...);
LIBTECH_API void LogWarning(const char* message, ...);
LIBTECH_API void LogError(const char* message, ...);

class LIBTECH_CLASS FileLogger
{
public:
    FileLogger();
    virtual ~FileLogger();

    bool enabled = true;

    void Open(const char* filepath);
    void Close();

    void LogTrace(const char* message, ...);
    void LogMessage(const char* message, ...);
    void LogWarning(const char* message, ...);
    void LogError(const char* message, ...);

private:
    enum LOG_LEVEL currentLevel;
    char** levelNames;

    FILE* logFile;

    void Log(enum LOG_LEVEL level, const char* message);
};