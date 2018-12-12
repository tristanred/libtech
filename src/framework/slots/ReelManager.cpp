#include "libtech/slots/ReelManager.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "libtech/slots/LineSet.h"
#include "libtech/slots/ReelStrip.h"
#include "libtech/slots/Paytable.h"
#include "libtech/slots/SymbolSet.h"
#include "libtech/slots/SlotWins.h"

ReelManager::ReelManager(int reels, int rows)
{
    isLoaded = false;

    this->Reels = reels;
    this->Rows = rows;

    this->ReelStops = new int[reels];
    this->ReelSymbols = new Symbol**[reels];
    for (int i = 0; i < reels; i++)
    {
        this->ReelSymbols[i] = new Symbol*[rows];
    }

    this->reelstrips = NULL;
    this->paytable = NULL;
    this->Lines = NULL;
    this->Symbols = NULL;

    this->LineWins = NULL;
    this->ScatterWins = NULL;
    this->wonAmount = 0;

    this->reelManagerSeed = (unsigned int)time(0);
    srand(this->reelManagerSeed);
    printf("Created ReelManager with seed %u\n", this->reelManagerSeed);
}

ReelManager::~ReelManager()
{
    this->CleanWins();
    if (LineWins != NULL)
    {
        delete[] this->LineWins;
    }

    if (this->ScatterWins != NULL)
    {
        delete(this->ScatterWins);
    }

    delete[] this->ReelStops;

    for (int i = 0; i < this->Reels; i++)
    {
        delete(this->reelstrips[i]);
    }
    delete[] this->reelstrips;

    for (int i = 0; i < this->Reels; i++)
    {
        delete[] this->ReelSymbols[i];
    }
    delete[] this->ReelSymbols;


    delete(this->paytable);
    delete(this->Lines);
    delete(this->Symbols);
}

LineWin** ReelManager::GetLineWins()
{
    return this->LineWins;
}

ScatterWin* ReelManager::GetScatterWins()
{
    return this->ScatterWins;
}

int ReelManager::GetWonAmount()
{
    return this->wonAmount;
}

void ReelManager::CreateDefaultObjects()
{
    this->Symbols = SymbolSet::CreateFromConfig(SYMBOLS_CFG_PATH);

    if (this->Symbols == NULL)
    {
        printf("Cannot load the Symbols config, aborting\n");
        return;
    }

    this->reelstrips = ReelStrip::GenerateReelstripSetFromConfig(REELSTRIP_CFG_PATH, this->Symbols, this->Reels);

    if (this->reelstrips == NULL)
    {
        printf("Cannot load the reelstrips config, aborting\n");
        return;
    }

    this->paytable = Paytable::GetPaytableFromConfig(PAYTABLE_CFG_PATH, this->Symbols);

    if (this->paytable == NULL)
    {
        printf("Cannot load the paytable config, aborting\n");
        return;
    }

    this->Lines = LineSet::CreateLinesetFromConfig(LINESET_CFG_PATH);

    if (this->Lines == NULL)
    {
        printf("Cannot load the lines config, aborting\n");
        return;
    }

    this->LineWins = new LineWin*[this->Lines->PatternsCount];
    for (int i = 0; i < this->Lines->PatternsCount; i++)
    {
        this->LineWins[i] = NULL;
    }

    this->isLoaded = true;
}

/**
 * Spin to win !
 * Theres a special define value to force the spin to a specific value.
 */
void ReelManager::Spin()
{
    if (this->isLoaded == false)
    {
        printf("ReelManager is not loaded.\n");
        return;
    }

#ifdef FAKE_SPIN
    this->ReelSymbols[0][0] = new Symbol(6);
    this->ReelSymbols[0][1] = new Symbol(1);
    this->ReelSymbols[0][2] = new Symbol(6);

    this->ReelSymbols[1][0] = new Symbol(6);
    this->ReelSymbols[1][1] = new Symbol(1);
    this->ReelSymbols[1][2] = new Symbol(6);

    this->ReelSymbols[2][0] = new Symbol(6);
    this->ReelSymbols[2][1] = new Symbol(0);
    this->ReelSymbols[2][2] = new Symbol(6);

    this->ReelSymbols[3][0] = new Symbol(6);
    this->ReelSymbols[3][1] = new Symbol(1);
    this->ReelSymbols[3][2] = new Symbol(6);

    this->ReelSymbols[4][0] = new Symbol(6);
    this->ReelSymbols[4][1] = new Symbol(1);
    this->ReelSymbols[4][2] = new Symbol(6);

    return;
#endif

    for (int i = 0; i < this->Reels; i++)
    {
        int rsLen = this->reelstrips[i]->Length;

        this->ReelStops[i] = this->reelstrips[i]->Symbols[rand() % rsLen]->id;

        for(int k = 0; k < this->Rows; k++)
        {
            this->ReelSymbols[i][k] = this->reelstrips[i]->Symbols[(this->ReelStops[i] + k) % rsLen];
        }
    }
}

/**
 * Augments the value of a symbol on the board. This will upgrade the symbol
 * to the next higher symbol. This always take the symbol that is 1 index under
 * the current symbol and depends on symbols being ordered by id in the
 * SymbolSet object.
 * Reel and Row parameter must be 1-based, not index values.
 */
void ReelManager::AugmentSymbol(int reel, int row)
{
    if (this->isLoaded == false)
    {
        printf("ReelManager is not loaded.\n");
        return;
    }

    if(reel > this->Reels || row > this->Rows)
    {
        printf("Bad parameter to Augment Symbol\n");

        return;
    }

    Symbol* sym = this->ReelSymbols[reel][row];

    if(sym->id > 0)
    {
        this->ReelSymbols[reel][row] = this->Symbols->SymbolList[sym->id - 1];
    }
}

/**
 * Select a single symbol and rerolls the value. The reroll will simply get
 * another symbol from the reelstrip and not just a random through the
 * game symbols.
 * Reel and Row parameter must be 1-based, not index values.
 */
void ReelManager::RespinSymbol(int reel, int row)
{
    if (this->isLoaded == false)
    {
        printf("ReelManager is not loaded.\n");
        return;
    }

    if(reel > this->Reels || row > this->Rows)
    {
        printf("Bad parameter to Augment Symbol\n");

        return;
    }

    int reelIndex = reel - 1;
    int rowIndex = row - 1;

    int rsLen = this->reelstrips[reelIndex]->Length;
    Symbol* newSymbol = this->reelstrips[reelIndex]->Symbols[rand() % rsLen];
    this->ReelSymbols[reelIndex][rowIndex] = newSymbol;
}

void ReelManager::PrintCurrentCombination()
{
    if (this->isLoaded == false)
    {
        printf("ReelManager is not loaded.\n");
        return;
    }

    for(int i = 0; i < this->Rows; i++)
    {
        printf("[%d, %d, %d, %d, %d]\n", this->ReelSymbols[0][i]->id,
                                         this->ReelSymbols[1][i]->id,
                                         this->ReelSymbols[2][i]->id,
                                         this->ReelSymbols[3][i]->id,
                                         this->ReelSymbols[4][i]->id);
    }
}

/**
 * Returns the total value won from the board.
 * The implementation is very primitive for now. Line wins are added
 * directly to scatter wins but scatter wins need to be multiplied to
 * total bet and line wins to line bet. We don't report anything else
 * than a number but we should report what other kind of prizes we won.
 * There is also no knowledge of money in the RM right now so line bet,
 * denom or other crap is not supported yet.
 */
int ReelManager::CalculateWins()
{
    if (this->isLoaded == false)
    {
        printf("ReelManager is not loaded.\n");
        return -1;
    }

    this->CleanWins();

    int totalWin = 0;

    Symbol** symbolsOnLine = new Symbol*[this->Reels];

    for(int i = 0; i < this->Lines->PatternsCount; i++)
    {
        for(int k = 0; k < this->Reels; k++)
        {
            int offset = this->Lines->LinePatterns[i][k];
            symbolsOnLine[k] = this->ReelSymbols[k][offset];
        }

        LineWin* wins = this->CalculateLineWin(symbolsOnLine);

        if(wins != NULL)
        {
            totalWin += wins->winAmount;

            wins->winLineIndex = i; // Hotfix winline

            printf("WinLine %d : Length = %d, Won = %d", i, wins->count, wins->winAmount);

            printf(" (");
            for (int k = 0; k < this->Reels; k++)
            {
                printf("%d ", symbolsOnLine[k]->id);
            }
            printf(")\n");

        }

        this->LineWins[i] = wins;
    }

    delete[] symbolsOnLine;

    ScatterWin* scatterWin = this->CalculateScatterWins();
    if(scatterWin != NULL)
    {
        totalWin += scatterWin->winAmount;

        printf("Scatter Win : Length = %d, Won %d\n", scatterWin->count, scatterWin->winAmount);
    }
    this->ScatterWins = scatterWin;

    return totalWin;
}

/**
 * Line win calculation method for a single line.
 * We take the symbols on a line and check them sequentially
 * to take the longest run of the same symbol starting from
 * left to right.
 *
 * Specific behavior :
 *  - A wild line always cede to the first non-wild symbol for its
 *    line pay. Wild lines can only pay if the entire line is Wild.
 *  - If multiple entries in the paytable exist for a winning
 *    combination, we always return the first one, not the most
 *    valuable one.
 */
LineWin* ReelManager::CalculateLineWin(Symbol** lineSymbols)
{
    if (this->isLoaded == false)
    {
        printf("ReelManager is not loaded.\n");
        return NULL;
    }

    // Start with the first symbol on the line
    Symbol* lineWinSymbol = lineSymbols[0];

    // Lines can't start with a scatter
    if (lineWinSymbol->isScatter)
    {
        return NULL;
    }

    // Win length value. This value is replaced each time
    // we find a new symbol on the line.
    int winLength = -1;

    /**
     * Go through each symbol on the rest of the line
     * This loop is a 'continue or beak' type. We start scanning
     * each payline from the left, if the win line is still valid
     * we 'continue' to the next loop. If we detect the line end
     * we 'break' out and start checking the payable if what we got
     * wins anything.
     */
    for(int i = 1; i < this->Reels; i++)
    {
        Symbol* sym = lineSymbols[i];

        // Scatters break lines
        if (sym->isScatter)
        {
            break;
        }

        // If the current line identity is Wild
        // Take the next symbol as the new line identity
        if(lineWinSymbol->isWild)
        {
            lineWinSymbol = sym;

            winLength = i + 1;

            continue;
        }

        // If the line has a symbol sequence but the next one is a wild
        // Increment the line length but do not change the identity of the winline to Wild.
        if(sym->isWild)
        {
            winLength = i + 1;

            continue;
        }

        // If we are the same symbol ID as the current sequence
        if(sym->id == lineWinSymbol->id)
        {
            winLength = i + 1;

            continue;
        }

        break;
    }

    // Check each win against the paytable
    for(int i = 0; i < this->paytable->PrizeCount; i++)
    {
        PaytablePrize* prize = this->paytable->Prizes[i];
        if(prize->SymbolCount == winLength && prize->SymbolID == lineWinSymbol->id)
        {
            LineWin* win = new LineWin();
            win->count = winLength;
            win->winAmount = prize->PrizeWins;
            win->WinningSymbol = new Symbol();
            memcpy(win->WinningSymbol, lineWinSymbol, sizeof(Symbol));
            win->winLineIndex = -1; // Don't know from here.

            return win;
        }
    }

    return NULL;
}

/**
 * Scatter win calculation method for the whole board.
 * We make a total of the scatters on the board and use that count
 * to find a prize in the paytable.
 *
 * Specific behavior :
 *  - Depending on the reelstrip, we may find more Scatters than the biggest
 *    prize advertized in the paytable. In this case we win nothing.
 *  - We accumulate symbols with isScatter == true. This means we don't support
 *    multiple scatter types.
 */
ScatterWin* ReelManager::CalculateScatterWins()
{
    if (this->isLoaded == false)
    {
        printf("ReelManager is not loaded.\n");
        return NULL;
    }

    ScatterWin* wins = new ScatterWin();

    Symbol* scatterSymbol = NULL;

    int scatterCount = 0;
    for(int i = 0; i < this->Reels; i++)
    {
        for(int k = 0; k < this->Rows; k++)
        {
            if(this->ReelSymbols[i][k]->isScatter)
            {
                scatterCount++;
                scatterSymbol = this->ReelSymbols[i][k];
            }
        }
    }

    if(scatterSymbol == NULL)
    {
        delete(wins);

        return NULL;
    }

    for(int i = 0; i < this->paytable->PrizeCount; i++)
    {
        PaytablePrize* prize = this->paytable->Prizes[i];

        if(prize->SymbolID == scatterSymbol->id && prize->SymbolCount == scatterCount)
        {
            wins->winAmount = prize->PrizeWins;
            wins->count = scatterCount;
            wins->WinningScatter = scatterSymbol;
            wins->winPositions = NULL; // Fuck it

            return wins;
        }
    }

    delete(wins);
    return NULL;
}

void ReelManager::CleanWins()
{
    for (int i = 0; i < this->Lines->PatternsCount; i++)
    {
        if (this->LineWins[i] != NULL)
        {
            delete(this->LineWins[i]);
            this->LineWins[i] = NULL;
        }
    }

    if (this->ScatterWins != NULL)
    {
        delete(this->ScatterWins);
        this->ScatterWins = NULL;
    }
}
