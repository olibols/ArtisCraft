#include "MasterRenderer.h"

#include <SFML/Graphics.hpp>

void MasterRenderer::drawQuad(glm::vec3 position) {
	m_quadRenderer.add(position);
}

void MasterRenderer::finishRender(sf::RenderWindow window, Camera camera) {
	glClearColor(0.1, 0.1, 1.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	m_quadRenderer.renderQuads(camera);

	window.display();

}