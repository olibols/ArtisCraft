#include "ParticleRenderer.h"

ParticleRenderer::ParticleRenderer()
{
	_shader = new ParticleShader;

	deltaClock.restart();
}

void ParticleRenderer::addParticle(BaseParticle& particle)
{
	auto& model = particle.model;

	ParticleMesh mesh;

	float s = particle.size;

	mesh.vertexPositions = {
		s, 0, 0,
		0, 0, 0,
		0, 0, 0,
		s, s, 0,

		//Front
		0, 0, s,
		s, 0, s,
		s, s, s,
		0, s, s,

		//Right
		s, 0, s,
		0.5, 0, 0,
		s, s, 0,
		s, s, s,

		//Left
		0, 0, 0,
		0, 0, s,
		0, s, s,
		0, s, 0,

		//Top
		0, s, s,
		s, s, s,
		s, s, 0,
		0, s, 0,

		//Bottom
		0, 0, 0,
		s, 0, 0,
		s, 0, s,
		0, 0, s
	};


	mesh.indices = {
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

	model.addData(mesh);

	_particles.push_back(particle);
}

void ParticleRenderer::processParticles()
{
	auto time = deltaClock.restart().asSeconds();

	for (auto& particle : _particles) {
		particle.processParticle(time);
	}
}

void ParticleRenderer::renderParticles(Camera & cam)
{
	_shader->useProgram();
	_shader->loadProjViewMatrix(cam.getProjViewMatrix());

	for (auto& particle : _particles) {		

		//if (particle.existedfor > particle.lifetime)
			//break;

		_shader->loadColour(particle.colour);
		particle.model.bindVAO();
		_shader->loadModelMatrix(makeModelMatrix({ particle.position.x, particle.position.y, particle.position.z }, { 0, 0, 0 }));
		glDrawElements(GL_TRIANGLES, particle.model.getIndicesCount(), GL_UNSIGNED_INT, 0);
	}

	processParticles();
}
