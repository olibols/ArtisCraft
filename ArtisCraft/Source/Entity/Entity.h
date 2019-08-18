#pragma once
#include "../AABB/AABB.h"
#include <GLM.h>

struct Entity {
	Entity() : hitbox({ 0, 0, 0 }) {} ;

	Entity(glm::vec3 pos, glm::vec3 rot, glm::vec3 box) : position(pos), rotation(rot), hitbox(box) {};

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
	glm::vec3 velocity;

	AABB hitbox;
};