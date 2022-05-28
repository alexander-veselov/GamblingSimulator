#include "Slot.h"

Slot::Slot(size_t linesCount, size_t reelsCount, const Symbols& symbols, const Lines& lines) :
    m_linesCount(linesCount), m_reelsCount(reelsCount),
    m_board(Board(linesCount, Line(reelsCount, symbols.GetRandomSymbol()))),
    m_symbols(symbols), m_lines(lines)
{}

void Slot::GenerateRandomBoard()
{
    for (size_t line = 0; line < m_linesCount; ++line)
    {
        for (size_t reel = 0; reel < m_reelsCount; ++reel)
        {
            m_board[line][reel] = m_symbols.GetRandomSymbol();
        }
    }
}

void Slot::SetBoard(const Board& board)
{
    m_board = board;
}

size_t Slot::MakeSpin()
{
    std::vector<Match> matches = m_lines.GetMatches(m_board);

    size_t pay = 0;
    for (const Match& m : matches)
    {
        pay += m.second.GetPay(m.first);
    }

    return pay;
}

const Board& Slot::GetBoard() const
{
    return m_board;
}