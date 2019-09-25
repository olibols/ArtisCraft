#pragma once
#include <SFML/Graphics.hpp>

#include "../Particle/Particle.h"
#include "Shaders/ParticleShader.h"
#include "../Model.h"
#include "../Camera.h"

class ParticleRenderer {
public:
	ParticleRenderer();

	void addParticle(BaseParticle& particle);
	void processParticles();

	void renderParticles(Camera& cam);
private:

	std::vector<BaseParticle> _particles;
	ParticleShader* _shader = nullptr;

	sf::Clock deltaClock;
};