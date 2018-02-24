#include "mytime.h"

#ifdef linux

#include <sys/time.h>

#endif

long get_a_ticks()
{
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0)
            return 0;

    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
