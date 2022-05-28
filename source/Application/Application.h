#pragma once

#include "ISubscriable.h"
#include "Display.h"
#include "../Core/Slot.h"

#include <memory>

class Application : public ISubscriable
{
public:
    Application(std::shared_ptr<IDisplay> display);
    void Process(Event event) override;
private:
    void OnKeyPressed();
private:
    Slot m_slot;
    std::shared_ptr<IDisplay> m_display;

    // TODO: extract to separate class
    size_t m_lastWin = 0;
    size_t m_wonTotal = 0;
    size_t m_spentTotal = 0;
};
