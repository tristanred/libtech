#pragma once

#include "SlotWins.h"

class ReelStrip;
class Paytable;
class LineSet;
class SymbolSet;
class Symbol;
class LineWin;

//#define FAKE_SPIN

class ReelManager
{
public:
    ReelManager(int reels, int rows);
    ~ReelManager();

    int Reels;
    int Rows;

    int* ReelStops;

    Symbol*** ReelSymbols; // Symbol*[Reels][Rows]

    ReelStrip** reelstrips;

    Paytable* paytable;

    LineSet* Lines;

    SymbolSet* Symbols;

    // Initialisation Methods

    void CreateDefaultObjects();

    // Gameplay methods
    void Spin();

    void PrintCurrentCombination();

    int CalculateWins();

    LineWin* CalculateLineWin(Symbol** lineSymbols);

    ScatterWin* CalculateScatterWins();

};