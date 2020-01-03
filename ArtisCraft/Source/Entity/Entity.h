#pragma once

#include <glm.hpp>

struct Entity {
	Entity(glm::vec3 pos, glm::vec3 rot) : position(pos), rotation(rot) {};
	Entity() = default;

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
	glm::vec3 velocity;
};