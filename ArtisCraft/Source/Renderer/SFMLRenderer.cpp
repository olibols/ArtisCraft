#include "SFMLRenderer.h"
#include <GL/glew.h>

void SFMLRenderer::add(sf::Drawable & thing)
{
	m_drawables.push_back(&thing);
}

void SFMLRenderer::render(sf::RenderWindow & window)
{
	if (m_drawables.empty())
		return;

	glDisable(GL_DEPTH_TEST);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);

	window.pushGLStates();
	window.resetGLStates();

	for (const auto& drawable : m_drawables)
	{
		window.draw(*drawable);
	}

	window.popGLStates();
	m_drawables.clear();
}