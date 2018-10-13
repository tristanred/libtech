#pragma once

/**
 * 5x3 template
 * +--+--+--+--+--+
 * |  |  |  |  |  |
 * +--+--+--+--+--+
 * |  |  |  |  |  |
 * +--+--+--+--+--+
 * |  |  |  |  |  |
 * +--+--+--+--+--+
 *
 * Sample set of 10 lines
 * 1) 1, 1, 1, 1, 1
 * 2) 0, 0, 0, 0, 0
 * 3) 2, 2, 2, 2, 2
 * 4) 0, 1, 2, 2, 2
 * 5) 2, 1, 0, 0, 0
 * 6) 0, 1, 2, 1, 0
 * 7) 2, 1, 0, 1, 2
 * 8) 0, 0, 1, 2, 2
 * 9) 2, 2, 1, 0, 0
 * 10)1, 0, 0, 0, 0
 *
*/

class LineSet
{
public:
    LineSet();
    LineSet(int** linePatterns, int patternCount);
    ~LineSet();

    int PatternsCount;
    int** LinePatterns;

    static LineSet* Generate10Lines();
};