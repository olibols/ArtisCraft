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
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				_quadRenderer->addQuad({ y, x, 0 });
			}
		}
	
		_quadRenderer->renderQuads(*_camera);
		_camera->update();

		_context->window.display();		
	}
}


void Application::handleInput()
{
}