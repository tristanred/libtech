#pragma once

class ReelStrip
{
public:
    ReelStrip();
    ReelStrip(int* symbols, int length);
    ~ReelStrip();

    int Length;
    int* Symbols;

    static ReelStrip* GenerateRandomReelstrip(int length, int symbolCount);
};