#include "Application.h"
#include "World/Chunk/ChunkMeshBuilder.h"

Application::Application(std::string windowName)
{
	_context = new RenderContext("ArtisCraft", 1280, 720);
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
		_renderMaster->finishRender(getWindow(), *_camera);

		handleEvents();
	}
}


void Application::handleEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		shouldUpdate = !shouldUpdate;
		sf::sleep(sf::Time(sf::seconds(0.2)));
	}
}	