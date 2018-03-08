#include <stdio.h>

// Use this to dynamically load the libTech DLL
#define DYNAMIC_DLL

#if defined(WIN32) && defined(DYNAMIC_DLL)
#include <Windows.h>

 typedef long (WINAPI *get_a_ticks_proc)();

#endif

#define LIBTECH_LOADDLL
#include <mytime\mytime.h>

int main(int argc, char** argv)
{
#if defined(WIN32) && defined(DYNAMIC_DLL)
    HMODULE libtech_mod = LoadLibrary(TEXT("libtechd.dll"));

    get_a_ticks_proc get_a_ticks = (get_a_ticks_proc)GetProcAddress(libtech_mod, "get_a_ticks");

    long x = get_a_ticks();

    printf("%li\n", x);

    return 0;
#else
    long x = get_a_ticks();

    printf("%li\n", x);

    return 0;
#endif
}