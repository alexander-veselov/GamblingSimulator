#pragma once

#include "Display.h"
#include "IEventListener.h"

#include <memory>
#include <queue>

struct IPlatform
{
    virtual std::shared_ptr<IDisplay> GetDisplay() = 0;
    virtual std::queue<Event> GetEvents() = 0;
};

std::shared_ptr<IPlatform> GetCurrentPlatform();