#include "MasterRenderer.h"

#include <SFML/Graphics.hpp>

void MasterRenderer::drawQuad(const glm::vec3& pos)
{
	m_quadRenderer.add(pos);
}

void MasterRenderer::finishRender(sf::RenderWindow& window, const Camera& camera)
{
	glClearColor(0.1, 0.25, 1.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	m_quadRenderer.renderQuads(camera);

	window.display();
}