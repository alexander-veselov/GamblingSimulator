#include "Application/Application.h"
#include "Application/EventLoop.h"
#include "Application/Platform.h"

int main()
{
	Platform platform;
	Application application(platform.GetDisplay());

	EventLoop eventLoop;
	eventLoop.Subscribe(std::make_shared<Application>(application));
	return eventLoop.Run();
}