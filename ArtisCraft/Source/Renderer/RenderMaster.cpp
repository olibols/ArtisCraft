#include "RenderMaster.h"

void RenderMaster::drawCube(glm::vec3 position)
{
	_cubeRenderer.addCube(position);
}

void RenderMaster::drawChunk(ChunkMesh & mesh)
{
	_chunkRenderer.add(mesh);
}

void RenderMaster::finishRender(sf::RenderWindow & window, Camera & camera)
{
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	srand(clok.getElapsedTime().asSeconds());

	_cubeRenderer.renderCubes(camera);
	_chunkRenderer.render(camera);

	window.display();
}
