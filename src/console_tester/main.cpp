#include <stdio.h>

// Use this to dynamically load the libTech DLL
#define DYNAMIC_DLL

#if defined(WIN32) && defined(DYNAMIC_DLL)
#include <Windows.h>

 typedef long (WINAPI *get_a_ticks_proc)();

#endif

#define LIBTECH_LOADDLL
#include <libtech/mytime.h>


#include <libtech/games/blackjack/blackjack.h>

#include <libtech/ReelManager.h>

int main(int argc, char** argv)
{
    ReelManager* rm = new ReelManager(5, 3);
    rm->CreateDefaultObjects();
    rm->Spin();
    rm->PrintCurrentCombination();

    delete(rm);


//    printf("Starting blackjack run");
//    {
//        BlackjackGame game;
//
//        while(game.CountGames < 20000)
//        {
//            game.UpdateGame();
//        }
//    }
//
//    printf("Finished running blackjack runs.");

    return 0;


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