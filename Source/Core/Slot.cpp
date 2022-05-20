#include "Slot.h"

Slot::Slot(size_t lines, size_t reels) :
    m_lines(lines), m_reels(reels)
{}

size_t Slot::MakeSpin() const
{
    return 0;
}