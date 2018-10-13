#pragma once

#include <random>
#include <stdlib.h>

class RandomGen
{
public:
    RandomGen(int seed = 0);
    ~RandomGen();

    int GetRandom(int min = 0, int outerMax = RAND_MAX);

    float GetRandomPercentage();
private:

};

int get_random_int(int min = 0, int outerMax = RAND_MAX);
float get_random_percent();
