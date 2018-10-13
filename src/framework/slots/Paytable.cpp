#include "Paytable.h"

#include <stdlib.h>

Paytable::Paytable()
{
    this->PrizeCount = 0;
    this->Prizes = NULL;
}

Paytable::~Paytable()
{
    for (int i = 0; i < this->PrizeCount; i++)
    {
        delete this->Prizes[i];
    }

    delete(this->Prizes);
}

Paytable* Paytable::GetDefaultPaytable(int* symbols, int symbolCount)
{
    Paytable* pt = new Paytable();
    pt->PrizeCount = symbolCount * 3;
    pt->Prizes = (PaytablePrize**)malloc(sizeof(PaytablePrize*) * pt->PrizeCount);

    int nextPrizeIndex = 0;
    int startingPrize = 5;
    for (int i = 0; i < symbolCount; i++)
    {
        PaytablePrize* prize = new PaytablePrize();
        prize->SymbolID = symbols[i];
        prize->SymbolCount = 3;
        prize->PrizeWins = startingPrize;
        pt->Prizes[nextPrizeIndex++] = prize;

        prize = new PaytablePrize();
        prize->SymbolID = symbols[i];
        prize->SymbolCount = 4;
        prize->PrizeWins = startingPrize * 2;
        pt->Prizes[nextPrizeIndex++] = prize;

        prize = new PaytablePrize();
        prize->SymbolID = symbols[i];
        prize->SymbolCount = 5;
        prize->PrizeWins = startingPrize * 3;
        pt->Prizes[nextPrizeIndex++] = prize;

        startingPrize = startingPrize * startingPrize;
    }

    return pt;
}

PaytablePrize::PaytablePrize()
{
    this->SymbolID = 0;
    this->SymbolCount = 0;
    this->PrizeWins = 0;
}

PaytablePrize::~PaytablePrize()
{

}
