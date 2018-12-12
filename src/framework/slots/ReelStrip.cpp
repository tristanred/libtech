#include "libtech/slots/ReelStrip.h"

#include <stdlib.h>
#include <time.h>

#include <libtech/stringtools.h>

#include "libtech/slots/SymbolSet.h"

#define PUGIXML_HEADER_ONLY
#include "pugixml.hpp"

ReelStrip::ReelStrip()
{
    this->Length = 0;
    this->Symbols = NULL;
}

ReelStrip::ReelStrip(Symbol** symbols, int length)
{
    this->Symbols = symbols;
    this->Length = length;
}

ReelStrip::~ReelStrip()
{
    delete[] this->Symbols;
}

ReelStrip** ReelStrip::GenerateReelstripSetFromConfig(const char* configPath, SymbolSet* symbols, int amount)
{
    if (amount == 0)
    {
        return NULL;
    }

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(configPath);
    if(!result)
    {
        // File not found
        return NULL;
    }

    ReelStrip** rs_set = new ReelStrip*[amount];
    for (int i = 0; i < amount; i++)
    {
        rs_set[i] = NULL;
    }

    // For now, read the reelstrip with id 0
    pugi::xpath_node_set reelStripNodes = doc.select_nodes("/reelsetConfig/reelset[@id = '0']/reelstrip");

    int rs_index = 0;
    for(pugi::xpath_node node: reelStripNodes)
    {
        pugi::xml_node reelStrip = node.node();

        const char* txt = reelStrip.text().as_string();

        long int numbersCount = 0;
        int* numbers = convert_string_to_int_list(txt, &numbersCount);

        rs_set[rs_index] = new ReelStrip();
        rs_set[rs_index]->Length = (int)numbersCount;
        rs_set[rs_index]->Symbols = new Symbol*[numbersCount];

        for (int i = 0; i < numbersCount; i++)
        {
            int num = numbers[i];

            Symbol* found = NULL;
            for(int k = 0; k < symbols->SymbolCount; k++)
            {
                if(symbols->SymbolList[k]->id == num)
                {
                    found = symbols->SymbolList[k];
                    break;
                }
            }

            if(found == NULL)
            {
                // Symbol in the strip is not found in the symbol set.
                break;
            }

            rs_set[rs_index]->Symbols[i] = found;
        }

        delete[] numbers;

        rs_index++;
    }

    return rs_set;
}

ReelStrip* ReelStrip::GenerateRandomReelstrip(int length, SymbolSet* symbols)
{
    ReelStrip* rs = new ReelStrip();

    rs->Length = length;
    rs->Symbols = new Symbol*[length];

    for (int i = 0; i < length; i++)
    {
        rs->Symbols[i] = symbols->SymbolList[rand() % symbols->SymbolCount];
    }

    return rs;
}
