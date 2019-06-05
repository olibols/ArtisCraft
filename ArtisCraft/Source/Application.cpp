#include "Application.h"
#include "Renderer/QuadRenderer.h"


Application::Application(std::string windowName)
{
	_context = new RenderContext(windowName, 1280, 720);
}

void Application::runLoop()
{
	glClearColor(0, 0.5f, 1.0f, 1.0f);

	sf::Clock dtTimer;

	while (true) {
		auto deltaTime = dtTimer.restart();

		_quadRenderer->addQuad({0, 0, 0});

		_context->window.display();
		handleInput();
	}
}

void Application::handleInput()
{
}
