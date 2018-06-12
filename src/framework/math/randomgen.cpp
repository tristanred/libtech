#include "libtech/randomgen.h"
#include "libtech/mytime.h"

RandomGen::RandomGen(int seed)
{
    if (seed == 0)
    {
        srand(get_a_ticks());
    }
    else
    {
        srand(seed);
    }
}


RandomGen::~RandomGen()
{
}

int RandomGen::GetRandom(int min, int outerMax)
{
    return rand() % (outerMax - min) + min;
}

float RandomGen::GetRandomPercentage()
{
    return (float)((rand() % 100) / 100.0);
}
