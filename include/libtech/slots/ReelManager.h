#pragma once

#include <libtech/libtech.h>

#include "SlotWins.h"

class ReelStrip;
class Paytable;
class LineSet;
class SymbolSet;
class Symbol;
class LineWin;
class ScatterWin;

//#define FAKE_SPIN

#define REELSTRIP_CFG_PATH "content/reelstrips.xml"
#define LINESET_CFG_PATH "content/lines.xml"
#define PAYTABLE_CFG_PATH "content/paytable.xml"
#define SYMBOLS_CFG_PATH "content/symbols.xml"

class LIBTECH_CLASS ReelManager
{
public:
    ReelManager(int reels, int rows);
    ~ReelManager();

    bool isLoaded;
    int Reels;
    int Rows;

    int* ReelStops;

    Symbol*** ReelSymbols;  // Symbol*[Reels][Rows]

    ReelStrip** reelstrips;

    Paytable* paytable;

    LineSet* Lines;

    SymbolSet* Symbols;

    LineWin** GetLineWins();
    ScatterWin* GetScatterWins();
    int GetWonAmount();

    unsigned int reelManagerSeed;

    // Initialisation Methods
    void CreateDefaultObjects();

    // Gameplay methods
    void Spin();

    void AugmentSymbol(int reel, int row);

    void RespinSymbol(int reel, int row);

    // Information methods
    void PrintCurrentCombination();

    // Wins & Reporting
    int CalculateWins();

    LineWin* CalculateLineWin(Symbol** lineSymbols);

    ScatterWin* CalculateScatterWins();

private:
    void CleanWins();

    // Previous result information
    LineWin** LineWins;
    ScatterWin* ScatterWins;
    int wonAmount;
};