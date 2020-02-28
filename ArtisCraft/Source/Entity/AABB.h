#pragma once

#include <glm.hpp>

// The struct/class that handles the box surrounding entities, used for collision detection.

struct AABB {
	AABB(glm::vec3 dim) : dimensions(dim) {}

	void update(glm::vec3 location) {
		position = location;
	}

	glm::vec3 position;
	glm::vec3 dimensions;
};