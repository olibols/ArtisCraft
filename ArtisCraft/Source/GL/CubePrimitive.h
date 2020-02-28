#pragma once

#include <vector>
#include <glm.hpp>
#include <GL/glew.h>

// Contains the primitives used in rendering

namespace primitives {
	const std::vector<GLfloat> CubeVertexes =
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,

		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,

		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,

		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,

		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,

		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};

	const std::vector<GLuint> CubeIndices = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	std::vector<GLfloat> createCubeColors(glm::vec3 color);
}