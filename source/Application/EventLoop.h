#pragma once

#include "Application/EventListener.h"

#include <vector>
#include <queue>

class IEventListener;
class Application;
struct SDL_Window;
struct SDL_Renderer;

class EventLoop
{
public:
    EventLoop();
    void AddEventListener(IEventListener* pEventListener);
    int Run(Application* pApplication);
    
private:
    void ProcessFrame();

private:
    std::vector<IEventListener*> m_EventListeners;
    std::queue<Event> m_eventQueue;
    bool m_bRunning = true;

    // TODO: refactor
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
};
