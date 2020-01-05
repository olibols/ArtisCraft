#pragma once

#include <GL\glew.h>
#include <vector>

struct Mesh {
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> vertexColors;
	std::vector<GLuint> indices;
};