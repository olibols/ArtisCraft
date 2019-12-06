#include "Application.h"

Application::Application(std::string windowName)
{
	m_context = new RenderContext(windowName, 1280, 720);
}

void Application::runLoop()
{

	while (true) {

	}
}

StateBase & Application::getState(std::string str)
{
	return *m_states[str];
}
