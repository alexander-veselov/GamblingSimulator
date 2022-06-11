#include "Application/Application.h"
#include "Application/EventLoop.h"
#include "Application/Platform.h"

#undef main

#include <iostream>

int main()
{
	std::shared_ptr<IPlatform> platform = GetCurrentPlatform();
	std::shared_ptr<Application> application(new Application(platform));
	
	EventLoop eventLoop(platform);
	eventLoop.AddEventListener(application);
	return eventLoop.Run(application);
}