#include <libtech/ReelManager.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <libtech/LineSet.h>
#include <libtech/ReelStrip.h>
#include <libtech/Paytable.h>
#include <libtech/SymbolSet.h>

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
    this->Symbols = NULL;
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
    srand(time(0));
    for (int i = 0; i < this->Reels; i++)
    {
        int rsLen = this->reelstrips[i]->Length;
        this->ReelStops[i] = this->reelstrips[i]->Symbols[rand() % rsLen]->id;

        for(int k = 0; k < this->Rows; k++)
        {
            this->ReelSymbols[i][k] = this->reelstrips[i]->Symbols[(this->ReelStops[i] + k) % rsLen]->id;
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

int ReelManager::CalculateWins()
{

    return 0;
}
