#include "PlayingState.h"
#include "../World/Chunk/ChunkMeshBuilder.h"
#include "../Application.h"
#include "../Util/Ray.h"


PlayingState::PlayingState(Application & app) : BaseState (app)
{
	app.getCamera().hookEntity(_player);

	//_world.editBlock(10, 10, 10, BlockID::Air);
}

void PlayingState::handleEvent(sf::Event event)
{
}

void PlayingState::handleInput()
{
	_player.handleInput(_application->getWindow());

	for (Ray ray(_player.position, _player.rotation); ray.getLength() < 6; ray.step(0.1)) {

		auto x = ray.getEnd().x;
		auto y = ray.getEnd().y;
		auto z = ray.getEnd().z;

		auto block = _world.getBlock(x, y, z);

		if (block != ChunkBlock(BlockID::Air) ){
			if (time.getElapsedTime().asSeconds() > 0.2) {

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					time.restart();
					_world.editBlock(x, y, z, 0);
					break;
				}
				else if ((sf::Mouse::isButtonPressed(sf::Mouse::Right))) {
					time.restart();
					_world.editBlock(lastPos.x,	lastPos.y, lastPos.z, BlockID::Stone);
				}
			}
		}
		lastPos = ray.getEnd();
	}	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
		_world.rebuildAll();

		sf::sleep(sf::Time(sf::seconds(0.2)));
	}
}

void PlayingState::update(float deltaTime)
{
	_player.update(deltaTime);
}

void PlayingState::render(RenderMaster & renderer)
{
	renderer.drawCube(lastPos);
	_world.render(renderer);
}
