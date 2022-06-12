#include "EventLoop.h"

#include "EventListener.h"
#include "Application.h"

#include <SDL.h>
#include <SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

EventLoop::EventLoop() {}

void EventLoop::AddEventListener(IEventListener* pEventListener)
{
    m_EventListeners.push_back(pEventListener);
}

int EventLoop::Run(Application* pApplication)
{
	SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

	SDL_CreateWindowAndRenderer(225, 225, 0, &m_window, &m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //SDL_RenderClear(m_renderer);
    //auto s = SDL_GetWindowSurface(window);
    pApplication->SetRenderer(m_renderer);

#if __EMSCRIPTEN__
	auto wrapper = [](void* arg) { static_cast<EventLoop*>(arg)->ProcessFrame(); };
	emscripten_set_main_loop_arg(wrapper, this, 0, true);
#else
	while (m_bRunning)
		ProcessFrame();
#endif

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	SDL_Quit();

    return 0;
}

void EventLoop::ProcessFrame()
{
	SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                m_eventQueue.push(Event::KEY_PRESSED);
            }
            break;
        case SDL_QUIT:
            m_bRunning = false;
            break;
        default:
            break;
        }
    }
    m_eventQueue.push(Event::IDLE);

	SDL_RenderClear(m_renderer);
    
    while (!m_eventQueue.empty())
    {
        Event e = m_eventQueue.front();
        m_eventQueue.pop();
        for (const auto& eventListener : m_EventListeners)
            eventListener->Handle(e);
    }

	SDL_RenderPresent(m_renderer);
}