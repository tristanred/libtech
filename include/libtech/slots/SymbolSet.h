#pragma once

#include <libtech/libtech.h>

class LIBTECH_CLASS Symbol
{
public:
    Symbol();
    Symbol(int id);
    ~Symbol();

    int id;
    char* name; // Optional
    bool isWild;
    bool isScatter;
};

class LIBTECH_CLASS SymbolSet
{
public:
    SymbolSet();
    ~SymbolSet();

    int SymbolCount;
    Symbol** SymbolList;

    static SymbolSet* CreateFromConfig(const char* configPath);
    static SymbolSet* CreateDefaultSet();
};