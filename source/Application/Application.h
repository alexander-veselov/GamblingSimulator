#pragma once

#include "Core/Slot.h"
#include "Display.h"
#include "EventListener.h"

class Application : public IEventListener
{
public:
    Application();
    void Handle(Event event) override;

    // TODO: remove this ridiculous shit
    void SetRenderer(SDL_Renderer* renderer);
private:
    void OnKeyPressed();
private:
    Slot m_slot;

    // TODO: extract to separate class
    size_t m_lastWin = 0;
    size_t m_wonTotal = 0;
    size_t m_spentTotal = 0;

    SDL_Renderer* renderer = nullptr;
};
