#pragma once

class PaytablePrize
{
public:
    PaytablePrize();
    ~PaytablePrize();

    int SymbolID;
    int SymbolCount;
    int PrizeWins;
};

class Paytable
{
public:
    Paytable();
    ~Paytable();

    static Paytable* GetDefaultPaytable(int* symbols, int symbolCount);

    int PrizeCount;
    PaytablePrize** Prizes;
};