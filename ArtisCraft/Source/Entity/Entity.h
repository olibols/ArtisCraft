#pragma once
#include <glm.hpp>

struct Entity {
	Entity() = default;

	Entity(glm::vec3 pos, glm::vec3 rot) : position(pos), rotation(rot) {};

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
	glm::vec3 velocity = { 0, 0, 0 };
};