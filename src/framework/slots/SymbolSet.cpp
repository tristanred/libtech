#include <libtech/SymbolSet.h>

#include <stdlib.h>

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

    delete(this->SymbolList);
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
    symWild->name = "WILD";
    symWild->isWild = true;
    symWild->isScatter = false;

    Symbol* symTop = new Symbol();
    symTop->id = 1;
    symTop->name = "TOPSYM";
    symTop->isWild = false;
    symTop->isScatter = false;

    Symbol* symA = new Symbol();
    symA->id = 2;
    symA->name = "ACE";
    symA->isWild = false;
    symA->isScatter = false;

    Symbol* symK = new Symbol();
    symK->id = 3;
    symK->name = "KING";
    symK->isWild = false;
    symK->isScatter = false;

    Symbol* symQ = new Symbol();
    symQ->id = 4;
    symQ->name = "QUEEN";
    symQ->isWild = false;
    symQ->isScatter = false;

    Symbol* symJ = new Symbol();
    symJ->id = 5;
    symJ->name = "JACK";
    symJ->isWild = false;
    symJ->isScatter = false;

    Symbol* symScatter = new Symbol();
    symScatter->id = 6;
    symScatter->name = "SCATTER";
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
