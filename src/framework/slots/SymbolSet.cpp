#include "libtech/slots/SymbolSet.h"

#include <stdlib.h>
#include <string.h>

#include "pugixml.hpp"

Symbol::Symbol()
{
    this->id = 0;
    this->name = NULL;
    this->isScatter = false;
    this->isWild = false;
}

Symbol::~Symbol()
{
    //delete(this->name);
}

Symbol::Symbol(int id)
{
    this->id = id;
    this->name = NULL;

    // Set to wild if ID is 0
    this->isWild = id == 0;

    // Set to wild id ID is 6
    this->isScatter = id == 6;
}

SymbolSet::SymbolSet()
{
    this->SymbolCount = 0;
    this->SymbolList = NULL;
}

SymbolSet::~SymbolSet()
{
    for(int i = 0; i < this->SymbolCount; i++)
    {
        delete(this->SymbolList[i]);
    }

    delete[] this->SymbolList;
}

SymbolSet* SymbolSet::CreateFromConfig(const char* configPath)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(configPath);
    if (!result)
    {
        // File not found
        return NULL;
    }

    pugi::xpath_node_set symbolNodes = doc.select_nodes("/symbolsetConfig/symbolset[@id='0']/symbol");

    SymbolSet* set = new SymbolSet();
    set->SymbolCount = (int)symbolNodes.size();
    set->SymbolList = new Symbol*[set->SymbolCount];

    for (pugi::xpath_node node : symbolNodes)
    {
        pugi::xml_node symbolNode = node.node();

        int symbolId = symbolNode.attribute("id").as_int();
        set->SymbolList[symbolId] = new Symbol();
        set->SymbolList[symbolId]->id = symbolId;

        const char* name = symbolNode.attribute("name").as_string();
        set->SymbolList[symbolId]->name = new char[strlen(name)];
        strcpy(set->SymbolList[symbolId]->name, name);


        set->SymbolList[symbolId]->isScatter = symbolNode.attribute("isScatter").as_bool();
        set->SymbolList[symbolId]->isWild = symbolNode.attribute("isWild").as_bool();
    }

    return set;
}

SymbolSet *SymbolSet::CreateDefaultSet()
{
    /**
     * Default set is 7 symbols
     * 0) Wild
     * 1) Top Symbol
     * 2) A
     * 3) K
     * 4) Q
     * 5) J
     * 9) Scatter
     */

    Symbol* symWild = new Symbol();
    symWild->id = 0;
    symWild->name = new char[SYMBOL_NAME_MAXLEN];
    strcpy(symWild->name, "WILD");
    symWild->isWild = true;
    symWild->isScatter = false;

    Symbol* symTop = new Symbol();
    symTop->id = 1;
    symTop->name = new char[SYMBOL_NAME_MAXLEN];
    strcpy(symTop->name, "TOPSYM");
    symTop->isWild = false;
    symTop->isScatter = false;

    Symbol* symA = new Symbol();
    symA->id = 2;
    symA->name = new char[SYMBOL_NAME_MAXLEN];
    strcpy(symA->name, "ACE");
    symA->isWild = false;
    symA->isScatter = false;

    Symbol* symK = new Symbol();
    symK->id = 3;
    symK->name = new char[SYMBOL_NAME_MAXLEN];
    strcpy(symK->name, "KING");
    symK->isWild = false;
    symK->isScatter = false;

    Symbol* symQ = new Symbol();
    symQ->id = 4;
    symQ->name = new char[SYMBOL_NAME_MAXLEN];
    strcpy(symQ->name, "QUEEN");
    symQ->isWild = false;
    symQ->isScatter = false;

    Symbol* symJ = new Symbol();
    symJ->id = 5;
    symJ->name = new char[SYMBOL_NAME_MAXLEN];
    strcpy(symJ->name, "JACK");
    symJ->isWild = false;
    symJ->isScatter = false;

    Symbol* symScatter = new Symbol();
    symScatter->id = 6;
    symScatter->name = new char[SYMBOL_NAME_MAXLEN];
    strcpy(symScatter->name, "SCATTER");
    symScatter->isWild = false;
    symScatter->isScatter = true;

    SymbolSet* set = new SymbolSet();
    set->SymbolCount = 7;
    set->SymbolList = new Symbol*[set->SymbolCount];

    set->SymbolList[0] = symWild;
    set->SymbolList[1] = symTop;
    set->SymbolList[2] = symA;
    set->SymbolList[3] = symK;
    set->SymbolList[4] = symQ;
    set->SymbolList[5] = symJ;
    set->SymbolList[6] = symScatter;

    return set;
}
