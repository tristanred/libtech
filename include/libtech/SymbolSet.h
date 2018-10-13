#pragma once

class Symbol
{
public:
    Symbol();
    Symbol(int id);
    ~Symbol();

    int id;
    const char* name; // Optional
    bool isWild;
    bool isScatter;
};

class SymbolSet
{
public:
    SymbolSet();
    ~SymbolSet();

    int SymbolCount;
    Symbol** SymbolList;

    static SymbolSet* CreateDefaultSet();
};