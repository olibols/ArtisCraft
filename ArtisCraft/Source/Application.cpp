#include "Application.h"
#include "World/Block/Chunk/ChunkMeshBuilder.h"

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

		state.handleInput();
		state.update(deltaTime.asSeconds());
		_camera->update();

		state.render(*_renderMaster);
		_renderMaster->finishRender(getWindow(), *_camera);

	}
}


void Application::handleInput()
{
	//if ();
}