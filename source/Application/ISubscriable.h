#pragma once

enum class Event
{
    IDLE = 0,
    UPDATE = 1,
    KEY_PRESSED = 2,
};

struct ISubscriable
{
    virtual void Process(Event event) = 0;
};