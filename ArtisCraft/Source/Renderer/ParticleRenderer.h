#pragma once
#include "../Particle/Particle.h"
#include "Shaders/ParticleShader.h"
#include "../Model.h"
#include "../Camera.h"

class ParticleRenderer {
public:
	ParticleRenderer();

	void addParticle(BaseParticle particle);
	void processParticles(float deltaTime);

	void renderParticles(Camera& cam);
private:

	Model * _particleModel = nullptr;
	std::vector<BaseParticle> _particles;
	ParticleShader* _shader = nullptr;

};