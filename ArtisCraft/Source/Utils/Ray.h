#pragma once

#include <glm.hpp>

class Ray {
public:
	Ray(glm::vec3 position, glm::vec3 direction);

	void step(float amount);

	glm::vec3 getEnd();

	float getLength();

private:

	glm::vec3 m_startPos;
	glm::vec3 m_endPos;
	glm::vec3 m_direction;
};