#pragma once
#include <GLM.h>

#include "ParticleModel.h"

struct BaseParticle {

	BaseParticle(glm::vec3 spawnPos, glm::vec3 spawnVelocity, float lifeSpan, glm::vec3 spawnColour, float size)
	:	lifetime(lifeSpan), position(spawnPos),
		velocity(spawnVelocity), size(size),
		colour(spawnColour)
	{};

	float lifetime;
	float existedfor;

	glm::vec3 position;
	glm::vec3 velocity;

	float size;
	glm::vec3 colour;

	void processParticle(float deltaTime);

	ParticleModel model;
};
