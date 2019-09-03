#pragma once

#include <GLM.h>

struct AABB {
	AABB(glm::vec3 dimensions) : dimensions(dimensions) {};
	
	void update(glm::vec3 location)
	{
		position = location;
	}

	glm::vec3 position;
	glm::vec3 dimensions;
};