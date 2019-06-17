#include "PlayingState.h"
#include "../World/Chunk/ChunkMeshBuilder.h"
#include "../Application.h"

PlayingState::PlayingState(Application & app) : BaseState (app)
{
	app.getCamera().hookEntity(_player);
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
	_world.render(renderer);
}
