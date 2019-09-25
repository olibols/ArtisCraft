#include "Particle.h"

void BaseParticle::processParticle(float deltaTime)
{
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	position.z += velocity.z * deltaTime;

	existedfor += deltaTime;
}
