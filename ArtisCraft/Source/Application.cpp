#include "Application.h"


Application::Application(std::string windowName)
{
	_context = new RenderContext("ArtisCraft", 1280, 720);
	_camera = new Camera();
	_quadRenderer = new QuadRenderer();

	_player = new Player();
}

void Application::runLoop()
{
	glClearColor(0, 0.5, 1.0, 1.0);

	_camera->hookEntity(*_player);

	sf::Clock dtTimer;

	while (true) {
		auto deltaTime = dtTimer.restart();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int z = 0; z < 10; z++) {
			for (int y = 0; y < 10; y++) {
				_quadRenderer->addQuad({ z, 0, y });
			}
		}	
	
		_player->handleInput();
		_player->update(deltaTime.asSeconds());
		_camera->update();
		_quadRenderer->renderQuads(*_camera);

		_context->window.display();		

		handleInput();
	}
}


void Application::handleInput()
{
	//if ();
}