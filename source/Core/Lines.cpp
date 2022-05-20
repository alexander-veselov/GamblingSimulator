#include "Lines.h"

Lines::Lines()
{
    m_lines.push_back({ 0, 0, 0 });
    m_lines.push_back({ 1, 1, 1 });
    m_lines.push_back({ 2, 2, 2 });
    m_lines.push_back({ 0, 1, 2 });
    m_lines.push_back({ 2, 1, 0 });
}

std::vector<Match> Lines::GetMatches(const Board& board) const
{
    std::vector<Match> matches;
    for (const std::vector<size_t>& line : m_lines)
    {
        Symbol symbol = board[line[0]][0];
        size_t matchesCount = 1;
        for (size_t i = 1; i < line.size(); ++i)
        {
            if (board[line[i]][i] == symbol)
                ++matchesCount;
        }
        if (matchesCount >= 3)
            matches.push_back({ matchesCount, symbol });
    }
    return matches;
}