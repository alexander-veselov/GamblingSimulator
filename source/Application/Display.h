#pragma once

#include <memory>

#include "../Core/Lines.h"

// TODO: make more generic
struct DisplayData
{
    DisplayData() = delete;
    DisplayData(size_t lastWin, size_t wonTotal, size_t spentTotal, const Board& board) :
        lastWin(lastWin), wonTotal(wonTotal), spentTotal(spentTotal), board(board)
    {}

    size_t lastWin = 0;
    size_t wonTotal = 0;
    size_t spentTotal = 0;
    const Board& board;
};

struct IDisplay
{
    virtual void Display(DisplayData displayData) const = 0;
};