#include "ReelManager.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "LineSet.h"
#include "ReelStrip.h"
#include "Paytable.h"

ReelManager::ReelManager(int reels, int rows)
{
    this->Reels = reels;
    this->Rows = rows;

    this->ReelStops = new int[reels];
    this->ReelSymbols = new int*[reels];
    for (int i = 0; i < reels; i++)
    {
        this->ReelSymbols[i] = new int[rows];
    }

    this->reelstrips = NULL;
    this->paytable = NULL;
    this->Lines = NULL;
}

ReelManager::~ReelManager()
{
    delete[] this->ReelStops;
    for (int i = 0; i < this->Reels; i++)
    {
        delete[] this->ReelSymbols[i];
    }
    delete[] this->ReelSymbols;

    delete(this->reelstrips);
    delete(this->paytable);
    delete(this->Lines);

}

void ReelManager::CreateDefaultObjects()
{
    int symbols[6] = { 0, 1, 2, 3, 4, 5 };
    this->reelstrips = new ReelStrip*[this->Reels];
    for (int i = 0; i < this->Reels; i++)
    {
        this->reelstrips[i] = ReelStrip::GenerateRandomReelstrip(20, 6);
    }

    this->paytable = Paytable::GetDefaultPaytable(symbols, 6);

    this->Lines = LineSet::Generate10Lines();
}

void ReelManager::Spin()
{
    srand(time(0));
    for (int i = 0; i < this->Reels; i++)
    {
        int rsLen = this->reelstrips[i]->Length;
        this->ReelStops[i] = this->reelstrips[i]->Symbols[rand() % rsLen];

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
        printf("[%d, %d, %d, %d, %d]\n", this->ReelSymbols[0][i],
                                         this->ReelSymbols[1][i],
                                         this->ReelSymbols[2][i],
                                         this->ReelSymbols[3][i],
                                         this->ReelSymbols[4][i]);
    }
}
