#include "PlayerDigEvent.h"
#include "../World.h"
#include <memory>

PlayerDigEvent::PlayerDigEvent(sf::Mouse::Button button, const glm::vec3& location, Player & player) : _buttonPress(button), _digSpot(location), _player(&player)
{
}

void PlayerDigEvent::handle(World & world)
{
	VectorXZ chunkLocation = World::getChunkXZ(_digSpot.x, _digSpot.z);
	if (world.getChunkManager().regionLoadedAt(chunkLocation.x, chunkLocation.z)) {
		dig(world);
	}

}

void PlayerDigEvent::dig(World & world)
{
	switch (_buttonPress) {
	case sf::Mouse::Button::Left:
		world.updateRegion(_digSpot.x, _digSpot.y, _digSpot.z);
		world.setBlock(_digSpot.x, _digSpot.y, _digSpot.z, 0);
		break;

	case sf::Mouse::Button::Right:
		world.updateRegion(_digSpot.x, _digSpot.y, _digSpot.z);
		world.setBlock(_digSpot.x, _digSpot.y, _digSpot.z, BlockID::Stone);
		break;

	default:
		break;
	}

}
