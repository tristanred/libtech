#include "libtech/mytime.h"

#ifdef linux

#include <sys/time.h>

#elif WIN32

#include <windows.h>

#elif __APPLE__

#include <sys/time.h>

#endif

long get_a_ticks()
{
#ifdef linux
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0)
            return 0;

    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#elif WIN32
    return GetTickCount();

#elif __APPLE__
    timeval time;
    gettimeofday(&time, NULL);
    long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);

    return millis;
#endif
}
