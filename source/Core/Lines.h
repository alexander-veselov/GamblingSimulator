#pragma once

#include <vector>

#include "Symbols.h"

typedef std::vector<Symbol> Line;
typedef std::vector<Line> Board;
typedef std::pair<size_t, Symbol> Match;

class Lines
{
public:
    Lines();
    std::vector<Match> GetMatches(const Board& board) const;
private:
    std::vector<std::vector<size_t>> m_lines;
};