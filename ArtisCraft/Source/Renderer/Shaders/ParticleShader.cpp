#include "ParticleShader.h"

ParticleShader::ParticleShader() : BlockShader("ParticleVertex", "ParticleFragment")
{
	getUniforms();
}

void ParticleShader::getUniforms()
{
	BlockShader::getUniforms();
}
