#include "Particle.h"

void BaseParticle::processParticle(float deltaTime)
{
	int x = position.x;
	int y = position.y;
	int z = position.z;

	position = { x += velocity.x * deltaTime, y += velocity.y * deltaTime, z += velocity.z * deltaTime };

	existedfor += deltaTime;
}
