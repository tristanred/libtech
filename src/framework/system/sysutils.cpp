#include "libtech/sysutils.h"

#ifdef _WIN32

#include "Windows.h"

#elif linux

#include <unistd.h>

#endif

#include <string.h>
#include <stdio.h>

char* get_working_directory()
{
#ifdef _WIN32
    DWORD buflen = MAX_PATH;
    char* path = new char[MAX_PATH];
    DWORD res = GetCurrentDirectoryA(buflen, path);

    if(res > 0)
    {
        return path;
    }
    else
    {
        DWORD err = GetLastError();

        print_win32_error(err);

        return "";
    }
#elif linux

    return get_current_dir_name();

#else
    char* path = new char[1];
    strcpy(path, "");

    return path;
#endif
}


#ifdef WIN32

LIBTECH_API void print_last_win32_error()
{
    DWORD err = GetLastError();
    print_win32_error(err);
}

LIBTECH_API void print_win32_error(DWORD errorCode)
{
    char* errMsg = get_win32_error_text(errorCode);
    fprintf(stderr, errMsg);
    delete(errMsg);
}

char* get_win32_error_text(DWORD errorCode)
{
    char* msg = new char[512];

    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)msg,
        0, NULL);

    return msg;
}

#endif