#include "ReelStrip.h"

#include <stdlib.h>
#include <time.h>

ReelStrip::ReelStrip()
{
    this->Length = 0;
    this->Symbols = NULL;
}

ReelStrip::ReelStrip(int* symbols, int length)
{
    this->Symbols = symbols;
    this->Length = length;
}

ReelStrip::~ReelStrip()
{
    delete(this->Symbols);
}

ReelStrip* ReelStrip::GenerateRandomReelstrip(int length, int symbolCount)
{
    srand(time(0));

    ReelStrip* rs = new ReelStrip();

    rs->Length = length;
    rs->Symbols = new int[length];

    for (int i = 0; i < length; i++)
    {
        rs->Symbols[i] = rand() % symbolCount;
    }

    return rs;
}
