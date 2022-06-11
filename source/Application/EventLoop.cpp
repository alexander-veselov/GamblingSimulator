#include "EventLoop.h"

#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

EventLoop::EventLoop(std::shared_ptr<IPlatform> platform)
    : m_platform(platform)
{}

void EventLoop::AddEventListener(std::shared_ptr<IEventListener> pEventListener)
{
    m_EventListeners.push_back(pEventListener);
}

SDL_Window* window;
SDL_Renderer* renderer;

int EventLoop::Run(std::shared_ptr<Application> application)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_CreateWindowAndRenderer(225, 225, 0, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, /* RGBA: green */ 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	auto s = SDL_GetWindowSurface(window);
	application->set(renderer);

#if __EMSCRIPTEN__
	auto wrapper = [](void* arg) { static_cast<EventLoop*>(arg)->ProcessFrame(); };
	emscripten_set_main_loop_arg(wrapper, this, 0, true);
#else
	while (true)
		ProcessFrame();
#endif

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

    return 0;
}

void EventLoop::ProcessFrame()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		return;
	}

	SDL_SetRenderDrawColor(renderer, /* RGBA: green */ 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
    m_eventQueue = m_platform->GetEvents();
	m_eventQueue.push(Event::IDLE);
    while (!m_eventQueue.empty())
    {
        Event e = m_eventQueue.front();
        m_eventQueue.pop();
        for (const auto& eventListener : m_EventListeners)
            eventListener->Handle(e);
    }
	SDL_RenderPresent(renderer);
}