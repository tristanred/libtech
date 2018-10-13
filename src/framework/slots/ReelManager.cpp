#include <libtech/ReelManager.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <libtech/LineSet.h>
#include <libtech/ReelStrip.h>
#include <libtech/Paytable.h>
#include <libtech/SymbolSet.h>
#include <libtech/SlotWins.h>

ReelManager::ReelManager(int reels, int rows)
{
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

    this->reelManagerSeed = (unsigned int)time(0);
    printf("Created ReelManager with seed %ld\n", this->reelManagerSeed);
}

ReelManager::~ReelManager()
{
    delete[] this->ReelStops;

    delete(this->reelstrips);
    delete(this->paytable);
    delete(this->Lines);
    delete(this->Symbols);
}

void ReelManager::CreateDefaultObjects()
{
    this->Symbols = SymbolSet::CreateDefaultSet();

    this->reelstrips = new ReelStrip*[this->Reels];
    for (int i = 0; i < this->Reels; i++)
    {
        this->reelstrips[i] = ReelStrip::GenerateRandomReelstrip(20, this->Symbols);
    }

    this->paytable = Paytable::GetDefaultPaytable(this->Symbols);

    this->Lines = LineSet::Generate10Lines();
}

void ReelManager::Spin()
{
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

    srand(this->reelManagerSeed);
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

void ReelManager::PrintCurrentCombination()
{
    for(int i = 0; i < this->Rows; i++)
    {
        printf("[%d, %d, %d, %d, %d]\n", this->ReelSymbols[0][i]->id,
                                         this->ReelSymbols[1][i]->id,
                                         this->ReelSymbols[2][i]->id,
                                         this->ReelSymbols[3][i]->id,
                                         this->ReelSymbols[4][i]->id);
    }
}

int ReelManager::CalculateWins()
{
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

            printf("WinLine %d : Length = %d, Won = %d", i, wins->count, wins->winAmount);

            printf(" (");
            for (int k = 0; k < this->Reels; k++)
            {
                printf("%d ", symbolsOnLine[k]->id);
            }
            printf(")\n");
            /*int* winPattern = this->Lines->LinePatterns[i];
            for (int k = 0; k < this->Reels; k++)
            {
                Symbol* winSymbol = this->ReelSymbols[k][winPattern[k]];

                printf("%d ");
            }*/
        }


        delete(wins);
    }

    delete(symbolsOnLine);

    ScatterWin* scatterWin = this->CalculateScatterWins();
    if(scatterWin != NULL)
    {
        totalWin += scatterWin->winAmount;

        printf("Scatter Win : Length = %d, Won %d\n", scatterWin->count, scatterWin->winAmount);
    }

    return totalWin;
}

LineWin* ReelManager::CalculateLineWin(Symbol** lineSymbols)
{
    // Start with the first symbol on the line
    Symbol* lineWinSymbol = lineSymbols[0];

    // Lines can't start with a scatter
    if (lineWinSymbol->isScatter)
    {
        return NULL;
    }

    // Win info
    int winLength = -1;
    int winSymbol = -1;
    int winAmount = -1;

    // Go through each symbol on the rest of the line
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
            win->WinningSymbol = lineWinSymbol;
            win->winLineIndex = -1; // Don't know from here.

            return win;
        }
    }

    return NULL;
}

ScatterWin* ReelManager::CalculateScatterWins()
{
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

    return NULL;
}
