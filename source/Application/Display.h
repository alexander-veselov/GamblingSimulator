#pragma once

#include "Core/Lines.h"

struct SDL_Renderer;

// TODO: make more generic
struct DisplayData
{
    DisplayData() = delete;
    DisplayData(size_t lastWin, size_t wonTotal, size_t spentTotal, const Board& board, SDL_Renderer* renderer) :
        lastWin(lastWin), wonTotal(wonTotal), spentTotal(spentTotal), board(board), renderer(renderer)
    {}

    size_t lastWin = 0;
    size_t wonTotal = 0;
    size_t spentTotal = 0;
    
    const Board& board;

    SDL_Renderer* renderer = nullptr;
};

void Display(DisplayData displayData);