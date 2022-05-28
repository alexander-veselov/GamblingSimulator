#pragma once

#include "Symbols.h"
#include "Lines.h"

#include <vector>

class Slot
{
public:
    Slot(size_t linesCount, size_t reelsCount, const Symbols& symbols, const Lines& lines);
    size_t MakeSpin();
    const Board& GetLastBoard() const;
private:
    size_t m_linesCount = 0;
    size_t m_reelsCount = 0;
    Board m_board;
    Lines m_lines;
    Symbols m_symbols;
};