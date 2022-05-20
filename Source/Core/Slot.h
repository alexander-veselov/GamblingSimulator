#pragma once

class Slot
{
public:
    Slot(size_t lines, size_t reels);
    size_t MakeSpin() const;
private:
    size_t m_lines = 0;
    size_t m_reels = 0;
};