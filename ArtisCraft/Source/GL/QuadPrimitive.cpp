#include "QuadPrimitive.h"

std::vector<GLfloat> QuadPrimitive::createQuadColors(glm::vec3 color)
{
	return {
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b
	};
}

