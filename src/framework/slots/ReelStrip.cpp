#include <libtech/ReelStrip.h>

#include <stdlib.h>
#include <time.h>

#include <libtech/SymbolSet.h>

ReelStrip::ReelStrip()
{
    this->Length = 0;
    this->Symbols = NULL;
}

ReelStrip::ReelStrip(Symbol** symbols, int length)
{
    this->Symbols = symbols;
    this->Length = length;
}

ReelStrip::~ReelStrip()
{
}

ReelStrip* ReelStrip::GenerateRandomReelstrip(int length, SymbolSet* symbols)
{
    ReelStrip* rs = new ReelStrip();

    rs->Length = length;
    rs->Symbols = new Symbol*[length];

    for (int i = 0; i < length; i++)
    {
        rs->Symbols[i] = symbols->SymbolList[rand() % symbols->SymbolCount];
    }

    return rs;
}
