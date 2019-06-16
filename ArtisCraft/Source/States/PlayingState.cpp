#include "PlayingState.h"
#include "../World/Block/Chunk/ChunkMeshBuilder.h"
#include "../Application.h"

PlayingState::PlayingState(Application & app) : BaseState (app)
{
	app.getCamera().hookEntity(_player);

	ChunkMeshBuilder builder(_chunk);
	builder.build(_chunk.mesh);

	_chunk.mesh.updateMesh();
}

void PlayingState::handleEvent(sf::Event event)
{
}

void PlayingState::handleInput()
{
	_player.handleInput(_application->getWindow());
}

void PlayingState::update(float deltaTime)
{
	_player.update(deltaTime);
}

void PlayingState::render(RenderMaster & renderer)
{
	renderer.drawChunk(_chunk.mesh);
}
