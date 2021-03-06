#include "libtech/filelogger.h"

#include <assert.h>
#include <string.h>

#include <cstdarg>
#include <string>
using namespace std;

FileLogger* _globalLogger = NULL;

void RegisterLogger(FileLogger* logger)
{
    if(_globalLogger != NULL)
    {
        delete(_globalLogger);
    }

    _globalLogger = logger;
}

void LogTrace(const char* message, ...)
{
    if(_globalLogger != NULL)
    {
        char msg[MSG_MAXBUF];
        va_list argptr;
        va_start(argptr, message);
        vsprintf(msg, message, argptr);
        va_end(argptr);

        _globalLogger->LogTrace(msg);

#ifdef BREAK_ON_TRACE
        assert(false);
#endif
    }
}

void LogMessage(const char* message, ...)
{
    if(_globalLogger != NULL)
    {
        char msg[MSG_MAXBUF];
        va_list argptr;
        va_start(argptr, message);
        vsprintf(msg, message, argptr);
        va_end(argptr);

        _globalLogger->LogMessage(message);

#ifdef BREAK_ON_MESSAGE
        assert(false);
#endif
    }
}

void LogWarning(const char* message, ...)
{
    if(_globalLogger != NULL)
    {
        char msg[MSG_MAXBUF];
        va_list argptr;
        va_start(argptr, message);
        vsprintf(msg, message, argptr);
        va_end(argptr);

        _globalLogger->LogWarning(message);

#ifdef BREAK_ON_WARNING
        assert(false);
#endif
    }
}

void LogError(const char* message, ...)
{
    if(_globalLogger != NULL)
    {
        char msg[MSG_MAXBUF];
        va_list argptr;
        va_start(argptr, message);
        vsprintf(msg, message, argptr);
        va_end(argptr);

        _globalLogger->LogError(message);

#ifdef BREAK_ON_ERROR
        assert(false);
#endif
    }
}

FileLogger::FileLogger()
{
    enabled = true;

    levelNames = new char*[LOG_LEVELCOUNT];

    const char* log_trace_name = "[TRACE]";
    const char* log_msg_name = "[MSG]";
    const char* log_warn_name = "[WARN]";
    const char* log_err_name = "[ERROR]";

    levelNames[LOG_TRACE] = new char[strlen(log_trace_name)];
    levelNames[LOG_MSG] = new char[strlen(log_msg_name)];
    levelNames[LOG_WARN] = new char[strlen(log_warn_name)];
    levelNames[LOG_ERROR] = new char[strlen(log_err_name)];

    strcpy(levelNames[LOG_TRACE], log_trace_name);
    strcpy(levelNames[LOG_MSG], log_msg_name);
    strcpy(levelNames[LOG_WARN], log_warn_name);
    strcpy(levelNames[LOG_ERROR], log_err_name);
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
        msg.append("\n");

        int result = fputs(msg.c_str(), logFile);

        if(result == EOF)
        {
            // Error
            fprintf(stderr, "Error printing log to file. %d", result);
        }

        printf("%s", msg.c_str());
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

void FileLogger::LogMessage(const char* message, ...)
{
    char msg[MSG_MAXBUF];
    va_list argptr;
    va_start(argptr, message);
    vsprintf(msg, message, argptr);
    va_end(argptr);

    this->Log(LOG_MSG, msg);
}

void FileLogger::LogWarning(const char* message, ...)
{
    char msg[MSG_MAXBUF];
    va_list argptr;
    va_start(argptr, message);
    vsprintf(msg, message, argptr);
    va_end(argptr);

    this->Log(LOG_WARN, msg);
}

void FileLogger::LogError(const char* message, ...)
{
    char msg[MSG_MAXBUF];
    va_list argptr;
    va_start(argptr, message);
    vsprintf(msg, message, argptr);
    va_end(argptr);

    this->Log(LOG_ERROR, msg);
}

void FileLogger::LogTrace(const char* message, ...)
{
    char msg[MSG_MAXBUF];
    va_list argptr;
    va_start(argptr, message);
    vsprintf(msg, message, argptr);
    va_end(argptr);

    this->Log(LOG_TRACE, msg);
}
