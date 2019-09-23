#pragma once
#include "BlockShader.h"

class ParticleShader : public BlockShader {
public:
	ParticleShader();

private:
	void getUniforms();
};