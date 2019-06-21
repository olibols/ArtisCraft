#include "Application.h"
#include "World/Chunk/ChunkMeshBuilder.h"

Application::Application(std::string windowName)
{
	_context = new RenderContext("ArtisCraft", 1920, 1080);
	_camera = new Camera();
	_renderMaster = new RenderMaster;

	_states.push_back(std::make_unique<PlayingState>(*this));
}

void Application::runLoop()
{
	sf::Clock dtTimer;


	while (true) {
		auto deltaTime = dtTimer.restart();
		BaseState& state = *_states.back();

		if (shouldUpdate) {
			state.handleInput();
			state.update(deltaTime.asSeconds());
		}

		_camera->update();

		state.render(*_renderMaster);

		handleEvents();
	}
}


void Application::handleEvents()
{
	sf::Event e;
	while (_context->window.pollEvent(e)) {
		switch (e.type) {

		case sf::Event::Closed:
			_context->window.close();

		case sf::Event::KeyPressed:
			switch (e.key.code) {
			case sf::Keyboard::Escape:
				shouldUpdate = !shouldUpdate;
				_context->window.setMouseCursorVisible(!shouldUpdate);
				sf::sleep(sf::Time(sf::seconds(0.2)));

			case sf::Keyboard::Up:
				fov++;
				_camera->newFov(fov);

			default:
				break;
			}				   

		default:
			break;
		}		
	}
}	