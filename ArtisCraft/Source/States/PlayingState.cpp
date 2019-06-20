#include "PlayingState.h"
#include "../World/Chunk/ChunkMeshBuilder.h"
#include "../Application.h"
#include "../Util/Ray.h"


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

	sf::Clock time;
	glm::vec3 lastPos;

	for (Ray ray(_player.position, _player.rotation);
		ray.getLength() < 6; ray.step(0.1)) {

		auto block = _world.getBlock(ray.getEnd().x, ray.getEnd().y, ray.getEnd().z);

		if (block.id != (Block_t)BlockID::Air) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				if (time.getElapsedTime().asSeconds() > 0.2) {
				{
					time.restart();
					_world.editBlock(ray.getEnd().x, ray.getEnd().y, ray.getEnd().z, 0);
					break;
				}
			}
		}
		lastPos = ray.getEnd();
	}	

}

void PlayingState::update(float deltaTime)
{
	_player.update(deltaTime);
}

void PlayingState::render(RenderMaster & renderer)
{
	_world.render(renderer);
}
