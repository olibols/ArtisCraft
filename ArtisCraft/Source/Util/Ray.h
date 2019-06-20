#pragma once

#include "GLM.h"

class Ray {
public:
	Ray(glm::vec3 position, glm::vec3 direction);

	void step(float amount);

	glm::vec3 getEnd();

	float getLength();

private:

	glm::vec3 _startPos;
	glm::vec3 _endPos;
	glm::vec3 _direction;	
};