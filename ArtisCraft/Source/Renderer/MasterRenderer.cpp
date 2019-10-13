#include "MasterRenderer.h"

void MasterRenderer::drawSFML(sf::Drawable & drawable)
{
	m_SFMLRenderer.add(drawable);
}

void MasterRenderer::finishRender(sf::RenderWindow & window)
{

	glClearColor(0.1, 0.5, 1.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	m_SFMLRenderer.render(window);

	window.display();
}