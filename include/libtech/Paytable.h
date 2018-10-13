#pragma once

class Symbol;
class SymbolSet;

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

    static Paytable* GetDefaultPaytable(SymbolSet* symbols);

    int PrizeCount;
    PaytablePrize** Prizes;
};