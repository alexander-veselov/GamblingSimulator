#include "EventLoop.h"

#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

EventLoop::EventLoop(std::shared_ptr<IPlatform> platform)
    : m_platform(platform)
{}

void EventLoop::AddEventListener(std::shared_ptr<IEventListener> pEventListener)
{
    m_EventListeners.push_back(pEventListener);
}

int EventLoop::Run()
{
#if __EMSCRIPTEN__
    auto wrapper = [](void *arg) { static_cast<EventLoop*>(arg)->ProcessFrame(); };
    emscripten_set_main_loop_arg(wrapper, this, 144, true);
#else
    while (true)
        ProcessFrame();
#endif
    return 0;
}

void EventLoop::ProcessFrame()
{
    m_eventQueue = m_platform->GetEvents();
    while (!m_eventQueue.empty())
    {
        Event e = m_eventQueue.front();
        m_eventQueue.pop();
        for (const auto& eventListener : m_EventListeners)
            eventListener->Handle(e);
    }
}