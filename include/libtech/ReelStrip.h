#pragma once

class SymbolSet;
class Symbol;

class ReelStrip
{
public:
    ReelStrip();
    ReelStrip(Symbol** symbols, int length);
    ~ReelStrip();

    int Length;
    Symbol** Symbols; // Borrowed list

    static ReelStrip* GenerateRandomReelstrip(int length, SymbolSet* symbols);
};