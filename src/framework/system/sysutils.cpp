#include "libtech/sysutils.h"

#ifdef _WIN32

#include "Windows.h"

#endif

#include <string.h>

char* get_working_directory()
{
#ifdef _WIN32
    DWORD buflen = MAX_PATH;
    char* path = new char[MAX_PATH];
    DWORD res = GetCurrentDirectoryA(buflen, path);
    
    if(SUCCEEDED(res))
    {
        return path;
    }
    else
    {
        return "";
    }
#else
    char* path = new char[1];
    strcpy(path, "");
    
    return path;
#endif
}