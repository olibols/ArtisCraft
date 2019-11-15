#include "PlayingState.h"
#include "../World/Chunk/ChunkMeshBuilder.h"
#include <thread>
#include "../Application.h"
#include "../Util/Ray.h"
#include "../World/Events/PlayerDigEvent.h"
#include <memory>


PlayingState::PlayingState(Application & app) : BaseState(app), _world(app.getCamera()), _frameCounter(app.getCamera())
{
	app.getCamera().hookEntity(_player);

	//_world.editBlock(10, 10, 10, BlockID::Air);
}

void PlayingState::handleEvent(sf::Event event)
{
}

void PlayingState::handleInput(RenderMaster& renderer)
{

	BaseParticle memeparticle({ 0, 0, 0 }, { 20, 0, 0 }, 50000, { 0, 1, 0 }, 0.5);

	_player.handleInput(_application->getWindow());

	for (Ray ray(_player.position, _player.rotation); ray.getLength() < 20; ray.step(0.1)) {

		auto x = ray.getEnd().x;
		auto y = ray.getEnd().y;
		auto z = ray.getEnd().z;

		auto block = _world.getBlock(x, y, z);

		if (block != ChunkBlock(BlockID::Air) ){
			if (time.getElapsedTime().asSeconds() > 0.2) {

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					time.restart();

					for(int x = -2; x < 2; x++)
					for(int y = -2; y < 2; y++)
					for (int z = -2; z < 2; z++) {
						glm::vec3 box ={ ray.getEnd().x + x, ray.getEnd().y + y, ray.getEnd().z + z };
						_world.addEvent<PlayerDigEvent>(sf::Mouse::Button::Left, box, _player);
					}
					break;
				}
				else if ((sf::Mouse::isButtonPressed(sf::Mouse::Right))) {
					time.restart();

					memeparticle.position = lastPos;

					renderer.addParticle(memeparticle);
					//_world.addEvent<PlayerDigEvent>(sf::Mouse::Button::Right, lastPos, _player);
					
					break;
				}
			}
		}
		lastPos = ray.getEnd();
	}	
}

void PlayingState::update(float deltaTime)
{
	if (_player.position.x < 0) _player.position.x = 0;
	if (_player.position.z < 0) _player.position.z = 0;

	_player.update(deltaTime, _world);
	_world.update(_application->getCamera());

	_frameCounter.update();

	//printf("%c", glGetError());
}

void PlayingState::render(RenderMaster & renderer)
{
	//renderer.drawCube({ _player.position.x - 0.25 ,_player.position.y - 3, _player.position.z - 0.25 });
	_world.render(renderer, _application->getCamera());
	_frameCounter.draw(renderer);
	_crosshair.draw(renderer);
	renderer.finishRender(_application->getWindow(), _application->getCamera());
}
