#include "Application.h"
#include "World/Block/Chunk/ChunkMeshBuilder.h"

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

	Chunk chunk;

	ChunkMeshBuilder builder(chunk);
	builder.build(chunk.mesh);

	chunk.mesh.updateMesh();

	while (true) {
		auto deltaTime = dtTimer.restart();

		_renderMaster->drawCube({ 0,0,0 });
		_renderMaster->drawChunk(chunk.mesh);
	
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