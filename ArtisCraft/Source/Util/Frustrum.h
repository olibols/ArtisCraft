#pragma once
#include <GLM.h>
#include <array>
#include "../AABB/AABB.h"

struct Plane {
	float distanceToPoint(glm::vec3& point);

	float distanceToOrigin = 0.0f;
	glm::vec3 normal;
};

class Frustrum {
public:
	void update(glm::mat4& projViewMatrix);

	bool isInFrustrum(AABB& box);

private:
	std::array<Plane, 6> _planes;
};