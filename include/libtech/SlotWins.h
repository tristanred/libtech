#pragma once

class Symbol;

class LineWin
{
public:
    LineWin();
    ~LineWin();

    int count;
    int winLineIndex;

    Symbol* WinningSymbol;

    int winAmount;
};

class ScatterWin
{
public:
    ScatterWin();
    ~ScatterWin();

    int count;
    int** winPositions; // int[reelPos][rowPos]

    Symbol* WinningScatter;

    int winAmount;
};

