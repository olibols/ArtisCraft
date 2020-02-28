#pragma once

#include <array>
#include <vector>
#include <gl/glew.h>

#include <glm.hpp>

// Primitives for rendering

namespace QuadPrimitive {

	const std::array<GLfloat, 12> FRONT_FACE = { 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1 };
	const std::array<GLfloat, 12> LEFT_FACE = { 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 };
	const std::array<GLfloat, 12> BACK_FACE = { 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0 };
	const std::array<GLfloat, 12> RIGHT_FACE = { 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0 };
	const std::array<GLfloat, 12> TOP_FACE = { 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1 };
	const std::array<GLfloat, 12> BOTTOM_FACE = { 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 };

	std::vector<GLfloat> createQuadColors(glm::vec3 color);
}