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
    pt->PrizeCount = 21;
    pt->Prizes = (PaytablePrize**)malloc(sizeof(PaytablePrize*) * pt->PrizeCount);

    // Symbol 0
    pt->Prizes[0] = new PaytablePrize();
    pt->Prizes[0]->SymbolID = 0;
    pt->Prizes[0]->PrizeWins = 1000;
    pt->Prizes[0]->SymbolCount = 5;

    pt->Prizes[1] = new PaytablePrize();
    pt->Prizes[1]->SymbolID = 0;
    pt->Prizes[1]->PrizeWins = 500;
    pt->Prizes[1]->SymbolCount = 4;

    pt->Prizes[2] = new PaytablePrize();
    pt->Prizes[2]->SymbolID = 0;
    pt->Prizes[2]->PrizeWins = 100;
    pt->Prizes[2]->SymbolCount = 3;

    // Symbol 1
    pt->Prizes[3] = new PaytablePrize();
    pt->Prizes[3]->SymbolID = 1;
    pt->Prizes[3]->PrizeWins = 800;
    pt->Prizes[3]->SymbolCount = 5;

    pt->Prizes[4] = new PaytablePrize();
    pt->Prizes[4]->SymbolID = 1;
    pt->Prizes[4]->PrizeWins = 500;
    pt->Prizes[4]->SymbolCount = 4;

    pt->Prizes[5] = new PaytablePrize();
    pt->Prizes[5]->SymbolID = 1;
    pt->Prizes[5]->PrizeWins = 200;
    pt->Prizes[5]->SymbolCount = 3;

    // Symbol 2
    pt->Prizes[6] = new PaytablePrize();
    pt->Prizes[6]->SymbolID = 2;
    pt->Prizes[6]->PrizeWins = 500;
    pt->Prizes[6]->SymbolCount = 5;

    pt->Prizes[7] = new PaytablePrize();
    pt->Prizes[7]->SymbolID = 2;
    pt->Prizes[7]->PrizeWins = 350;
    pt->Prizes[7]->SymbolCount = 4;

    pt->Prizes[8] = new PaytablePrize();
    pt->Prizes[8]->SymbolID = 2;
    pt->Prizes[8]->PrizeWins = 100;
    pt->Prizes[8]->SymbolCount = 3;

    // Symbol 3
    pt->Prizes[9] = new PaytablePrize();
    pt->Prizes[9]->SymbolID = 3;
    pt->Prizes[9]->PrizeWins = 300;
    pt->Prizes[9]->SymbolCount = 5;

    pt->Prizes[10] = new PaytablePrize();
    pt->Prizes[10]->SymbolID = 3;
    pt->Prizes[10]->PrizeWins = 200;
    pt->Prizes[10]->SymbolCount = 4;

    pt->Prizes[11] = new PaytablePrize();
    pt->Prizes[11]->SymbolID = 3;
    pt->Prizes[11]->PrizeWins = 100;
    pt->Prizes[11]->SymbolCount = 3;

    // Symbol 4
    pt->Prizes[12] = new PaytablePrize();
    pt->Prizes[12]->SymbolID = 4;
    pt->Prizes[12]->PrizeWins = 50;
    pt->Prizes[12]->SymbolCount = 5;

    pt->Prizes[13] = new PaytablePrize();
    pt->Prizes[13]->SymbolID = 4;
    pt->Prizes[13]->PrizeWins = 30;
    pt->Prizes[13]->SymbolCount = 4;

    pt->Prizes[14] = new PaytablePrize();
    pt->Prizes[14]->SymbolID = 4;
    pt->Prizes[14]->PrizeWins = 15;
    pt->Prizes[14]->SymbolCount = 3;

    // Symbol 5
    pt->Prizes[15] = new PaytablePrize();
    pt->Prizes[15]->SymbolID = 5;
    pt->Prizes[15]->PrizeWins = 20;
    pt->Prizes[15]->SymbolCount = 5;

    pt->Prizes[16] = new PaytablePrize();
    pt->Prizes[16]->SymbolID = 5;
    pt->Prizes[16]->PrizeWins = 10;
    pt->Prizes[16]->SymbolCount = 4;

    pt->Prizes[17] = new PaytablePrize();
    pt->Prizes[17]->SymbolID = 5;
    pt->Prizes[17]->PrizeWins = 5;
    pt->Prizes[17]->SymbolCount = 3;

    // Symbol 6
    pt->Prizes[18] = new PaytablePrize();
    pt->Prizes[18]->SymbolID = 6;
    pt->Prizes[18]->PrizeWins = 2000;
    pt->Prizes[18]->SymbolCount = 5;

    pt->Prizes[19] = new PaytablePrize();
    pt->Prizes[19]->SymbolID = 6;
    pt->Prizes[19]->PrizeWins = 1000;
    pt->Prizes[19]->SymbolCount = 4;

    pt->Prizes[20] = new PaytablePrize();
    pt->Prizes[20]->SymbolID = 6;
    pt->Prizes[20]->PrizeWins = 500;
    pt->Prizes[20]->SymbolCount = 3;

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
