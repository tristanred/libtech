#include "libtech/slots/SlotWins.h"

#include "libtech/slots/SymbolSet.h"

LineWin::LineWin() {}

LineWin::~LineWin()
{
    delete(this->WinningSymbol);
}

ScatterWin::ScatterWin() {}

ScatterWin::~ScatterWin() {}
