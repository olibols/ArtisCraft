#include "RenderMaster.h"

void RenderMaster::drawCube(glm::vec3 position)
{
	_cubeRenderer.addCube(position);
}

void RenderMaster::drawChunk(ChunkMesh & chunkMesh)
{
	_chunkRenderer.add(chunkMesh);
}

void RenderMaster::drawSFML(sf::Drawable & drawable)
{
	_SFMLRenderer.add(drawable);
}

void RenderMaster::addParticle(BaseParticle & particle)
{
	_particleRenderer.addParticle(particle);
}

void RenderMaster::finishRender(sf::RenderWindow & window, Camera & camera)
{
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	_cubeRenderer.renderCubes(camera);
	_chunkRenderer.render(camera);
	_SFMLRenderer.render(window);
	_particleRenderer.renderParticles(camera);

	window.display();
}
