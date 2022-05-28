#include "EventLoop.h"

#include <Windows.h> // TODO: kill yourself

void EventLoop::Subscribe(std::shared_ptr<ISubscriable> pSubscriable)
{
    m_subcribed.push_back(pSubscriable);
}

std::vector<Event> EventLoop::GetEvents() const
{
    if (GetAsyncKeyState(VK_SPACE) & 0x80000000)
        return { Event::KEY_PRESSED, Event::UPDATE };
    return { Event::IDLE };
}

int EventLoop::Run() const
{
    while (true)
    {
        for (Event e : GetEvents())
            for (const auto& subscriable : m_subcribed)
                subscriable->Process(e);
    }
    return 0;
}