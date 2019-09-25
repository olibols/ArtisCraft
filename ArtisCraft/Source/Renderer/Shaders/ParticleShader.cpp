#include "ParticleShader.h"

ParticleShader::ParticleShader() : BlockShader("ParticleVertex", "ParticleFragment")
{
	getUniforms();
}

void ParticleShader::getUniforms()
{
	BlockShader::getUniforms();
	_locColour = glGetUniformLocation(_ID, "colour");
}

void ParticleShader::loadColour(glm::vec3 colour)
{
	loadVector3(_locColour, colour);
}
