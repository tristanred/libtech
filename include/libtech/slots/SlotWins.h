#pragma once

#include <libtech/libtech.h>

class Symbol;

class LIBTECH_CLASS LineWin
{
public:
    LineWin();
    ~LineWin();

    int count;
    int winLineIndex;

    Symbol* WinningSymbol; // Copy of the symbol, owned pointer.

    int winAmount;
};

class LIBTECH_CLASS ScatterWin
{
public:
    ScatterWin();
    ~ScatterWin();

    int count;
    int** winPositions; // int[reelPos][rowPos]

    Symbol* WinningScatter; // Copy of the symbol, owned pointer.

    int winAmount;
};

class LIBTECH_CLASS SpecialWin
{
public:
    SpecialWin();
    ~SpecialWin();

    int FreeGamesWon;
};