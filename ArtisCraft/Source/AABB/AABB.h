#pragma once

#include <GLM.h>

struct AABB {
	AABB(glm::vec3 dimensions) : dimensions(dimensions) {};
	
	void update(glm::vec3 location)
	{
		position = location;
	}

	glm::vec3 getVN(glm::vec3& normal) {
		glm::vec3 res = position;

		if (normal.x < 0)
		{
			res.x += dimensions.x;
		}
		if (normal.y < 0)
		{
			res.y += dimensions.y;
		}
		if (normal.z < 0)
		{
			res.z += dimensions.z;
		}

		return res;
	}

	glm::vec3 getVP(glm::vec3& normal)
	{
		glm::vec3 res = position;

		if (normal.x > 0)
		{
			res.x += dimensions.x;
		}
		if (normal.y > 0)
		{
			res.y += dimensions.y;
		}
		if (normal.z > 0)
		{
			res.z += dimensions.z;
		}

		return res;
	}


	glm::vec3 position;
	glm::vec3 dimensions;
};