#pragma once
#include <GLM.h>

struct Entity {
	Entity() {};

	Entity(glm::vec3 pos, glm::vec3 rot) : position(pos), rotation(rot) {};

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
	glm::vec3 velocity = { 0, 0, 0 };

	float health = 10.0f;

};