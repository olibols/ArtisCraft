#include "MasterRenderer.h"

void MasterRenderer::drawBlock(glm::vec3 pos)
{
	m_blockRenderer.addBlock(pos);
}

void MasterRenderer::drawChunk(ChunkMesh & chunk)
{
	m_chunkRenderer.addChunk(chunk);
}

void MasterRenderer::clearChunks()
{
	m_chunkRenderer.clearChunks();
}

void MasterRenderer::finishRender(sf::RenderWindow & window, Camera & camera)
{
	glClearColor(80 / 250.0, 200 / 250.0, 198 / 250.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_blockRenderer.render(camera);
	m_chunkRenderer.render(camera);

	window.display();
}
