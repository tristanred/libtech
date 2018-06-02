#include "libtech/mytime.h"

#ifdef linux

#include <sys/time.h>

#elif WIN32

#include <windows.h>

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

#else
    return 0;

#endif
}
