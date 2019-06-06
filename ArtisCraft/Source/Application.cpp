#include "Application.h"


Application::Application(std::string windowName)
{
	_context = new RenderContext("ArtisCraft", 1280, 720);
	_camera = new Camera();

	_quadRenderer = new QuadRenderer();
}

void Application::runLoop()
{
	glClearColor(0, 0.5, 1.0, 1.0);

	while (true) {
		glClear(GL_COLOR_BUFFER_BIT);
		_quadRenderer->addQuad({ 0, 0, 0 });
		_quadRenderer->renderQuads(*_camera);

		_context->window.display();		
	}
}


void Application::handleInput()
{
}