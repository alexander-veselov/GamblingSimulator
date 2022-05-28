#pragma once

#include "IEventListener.h"
#include "Application/Platform.h"

#include <memory>
#include <vector>
#include <queue>

class EventLoop
{
public:
    EventLoop(std::shared_ptr<IPlatform> platform);
    void AddEventListener(std::shared_ptr<IEventListener> pEventListener);
    int Run();
    void ProcessFrame();
private:
    std::vector<std::shared_ptr<IEventListener>> m_EventListeners;
    std::queue<Event> m_eventQueue;
    std::shared_ptr<IPlatform> m_platform;
};
