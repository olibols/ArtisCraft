#include "MasterRenderer.h"

void MasterRenderer::drawBlock(glm::vec3 pos)
{
	m_blockRenderer.addBlock(pos);
}

void MasterRenderer::finishRender(sf::RenderWindow & window, Camera & camera)
{
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_blockRenderer.render(camera);
}
