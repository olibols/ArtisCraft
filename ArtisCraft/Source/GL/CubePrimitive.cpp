#include "CubePrimitive.h"

// I'm sorry this is all horrible but it works really nicely

std::vector<GLfloat> primitives::createCubeColors(glm::vec3 color)
{
	return {
	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,

	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,

	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,

	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,

	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,

	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b,
	color.r, color.g, color.b };
}
