#include "Application.h"

Application::Application(std::string windowName)
{
	_context = new RenderContext("ArtisCraft", Settings::width, Settings::height);
	_camera = new Camera();
	_renderMaster = new RenderMaster;

	_states.push_back(std::make_unique<PlayingState>(*this));

	_context->window.setMouseCursorVisible(false);
}

void Application::runLoop()
{
	sf::Clock dtTimer;
	BaseState& state = *_states.back();

	while (true) {
		auto deltaTime = dtTimer.restart();
		
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

			default:
				break;
			}				   

		default:
			break;
		}		
	}
}	