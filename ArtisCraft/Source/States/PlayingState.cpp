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

	sf::Clock time;

	for (Ray ray(_player.position, _player.rotation); ray.getLength() < 6; ray.step(0.1)) {

		auto x = ray.getEnd().x;
		auto y = ray.getEnd().y;
		auto z = ray.getEnd().z;

		auto block = _world.getBlock(x, y, z);

		if (block != ChunkBlock(BlockID::Air) ){
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				//if (time.getElapsedTime().asMilliseconds() > 200) {
					time.restart();
					_world.editBlock(x, y, z, 0);
					//sf::sleep(sf::Time(sf::seconds(0.2)));
					break;
				//}
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
	_cuberenderer.addCube(lastPos);

	_cuberenderer.renderCubes();

	_world.render(renderer);
}
