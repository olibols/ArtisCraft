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
