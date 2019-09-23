#pragma once
#include <GLM.h>

struct BaseParticle {
	float lifetime;
	float existedfor;

	glm::vec3 position;
	glm::vec3 velocity;

	float size;
	glm::vec3 colour;
};
