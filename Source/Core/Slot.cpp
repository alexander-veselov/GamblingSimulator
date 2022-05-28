#include "Slot.h"

Slot::Slot(size_t linesCount, size_t reelsCount, const Symbols& symbols, const Lines& lines) :
    m_linesCount(linesCount), m_reelsCount(reelsCount),
    m_board(Board(linesCount, Line(reelsCount, symbols.GetRandomSymbol()))),
    m_symbols(symbols), m_lines(lines)
{}

size_t Slot::MakeSpin()
{
    for (size_t line = 0; line < m_linesCount; ++line)
    {
        for (size_t reel = 0; reel < m_reelsCount; ++reel)
        {
            m_board[line][reel] = m_symbols.GetRandomSymbol();
        }
    }
    std::vector<Match> matches = m_lines.GetMatches(m_board);

    size_t pay = 0;
    for (const Match& m : matches)
    {
        pay += m.second.GetPay(m.first);
    }

    return pay;
}

const Board& Slot::GetLastBoard() const
{
    return m_board;
}