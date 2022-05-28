#pragma once

#include "../Display.h"

class WindowsUI : public IDisplay
{
public:
    void Display(DisplayData displayInfo) const override;
};