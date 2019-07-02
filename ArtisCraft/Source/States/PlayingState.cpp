#include "PlayingState.h"
#include "../World/Chunk/ChunkMeshBuilder.h"
#include <thread>
#include "../Application.h"
#include "../Util/Ray.h"


PlayingState::PlayingState(Application & app) : BaseState (app)
{
	_app = &app;

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
			//if (time.getElapsedTime().asSeconds() > 0.2) {

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					time.restart();
					sf::Clock clok;
					_world.setBlock(x, y, z, 0);
					printf("Took %f seconds to edit the block", clok.getElapsedTime().asSeconds());
					break;
				}
				else if ((sf::Mouse::isButtonPressed(sf::Mouse::Right))) {
					time.restart();
					_world.setBlock(lastPos.x,	lastPos.y, lastPos.z, BlockID::Stone);
					break;
				}
			//}
		}
		lastPos = ray.getEnd();
	}	
}

void PlayingState::update(float deltaTime)
{
	_player.update(deltaTime);
	_frameCounter.update();
}

void PlayingState::render(RenderMaster & renderer)
{
	renderer.drawCube({ _player.position.x - 250 ,_player.position.y - 250, _player.position.z -250});
	_world.render(renderer);
	_frameCounter.draw(renderer);
	_crosshair.draw(renderer);
	renderer.finishRender(_app->getWindow(), _app->getCamera());
}
