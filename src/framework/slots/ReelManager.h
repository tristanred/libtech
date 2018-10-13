#pragma once

class ReelStrip;
class Paytable;
class LineSet;

class ReelManager
{
public:
    ReelManager(int reels, int rows);
    ~ReelManager();


    int Reels;
    int Rows;

    int* ReelStops;

    int** ReelSymbols; // int[Reels][Rows]

    ReelStrip** reelstrips;

    Paytable* paytable;

    LineSet* Lines;

    // Initialisation Methods

    void CreateDefaultObjects();

    // Gameplay methods
    void Spin();

    void PrintCurrentCombination();

};