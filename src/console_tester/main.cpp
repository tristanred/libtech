#include <stdio.h>

// Use this to dynamically load the libTech DLL
#define DYNAMIC_DLL

#if defined(WIN32) && defined(DYNAMIC_DLL)
#include <Windows.h>

 typedef long (WINAPI *get_a_ticks_proc)();

#endif

#define LIBTECH_LOADDLL
#include <libtech/mytime.h>

#include <libtech/slots/ReelManager.h>

int main(int argc, char** argv)
{
    ReelManager* rm = new ReelManager(5, 3);
    rm->CreateDefaultObjects();
    rm->Spin();
    rm->PrintCurrentCombination();

    int res = rm->CalculateWins();

    printf("Won: %d", res);

    delete(rm);
}