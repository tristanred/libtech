#include <libtech/Paytable.h>

#include <stdlib.h>

#include <libtech/SymbolSet.h>

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

Paytable* Paytable::GetDefaultPaytable(SymbolSet* symbols)
{
    int initialPaytablePrizeSymbolsCount = 3;

    Paytable* pt = new Paytable();
    pt->PrizeCount = initialPaytablePrizeSymbolsCount * 3;
    pt->Prizes = (PaytablePrize**)malloc(sizeof(PaytablePrize*) * pt->PrizeCount);

    int nextPrizeIndex = 0;
    int startingPrize = 5;
    for (int i = 0; i < initialPaytablePrizeSymbolsCount; i++)
    {
        PaytablePrize* prize = new PaytablePrize();
        prize->SymbolID = symbols->SymbolList[i]->id;
        prize->SymbolCount = 3;
        prize->PrizeWins = startingPrize;
        pt->Prizes[nextPrizeIndex++] = prize;

        prize = new PaytablePrize();
        prize->SymbolID = symbols->SymbolList[i]->id;
        prize->SymbolCount = 4;
        prize->PrizeWins = startingPrize * 2;
        pt->Prizes[nextPrizeIndex++] = prize;

        prize = new PaytablePrize();
        prize->SymbolID = symbols->SymbolList[i]->id;
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
