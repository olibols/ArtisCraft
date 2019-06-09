#include "Application.h"


Application::Application(std::string windowName)
{
	_context = new RenderContext("ArtisCraft", 1280, 720);
	_camera = new Camera();
	_renderMaster = new RenderMaster;

	_player = new Player();
}

void Application::runLoop()
{
	_camera->hookEntity(*_player);

	sf::Clock dtTimer;

	while (true) {
		auto deltaTime = dtTimer.restart();

		_renderMaster->drawCube({ 0,0,0 });
	
		_player->handleInput(_context->window);
		_player->update(deltaTime.asSeconds());
		_camera->update();
		_renderMaster->finishRender(_context->window, *_camera);

		handleInput();
	}
}


void Application::handleInput()
{
	//if ();
}