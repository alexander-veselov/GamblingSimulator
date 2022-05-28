#pragma once

#include "Display.h"

#include <memory>

class Platform
{
public:
    Platform();
    std::shared_ptr<IDisplay> GetDisplay() const;
private:
    std::shared_ptr<IDisplay> m_pDisplay;
};