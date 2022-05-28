#pragma once

enum class Event
{
    IDLE = 0,
    UPDATE = 1,
    KEY_PRESSED = 2,
};

struct IEventListener
{
    virtual void Handle(Event event) = 0;
};