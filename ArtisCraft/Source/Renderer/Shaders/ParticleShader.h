#pragma once
#include "BlockShader.h"

class ParticleShader : public BlockShader {
public:
	ParticleShader();

	void loadColour(glm::vec3 colour);

private:
	void getUniforms();

	GLuint _locColour;
};