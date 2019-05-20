#include "Application.h"

Application::Application(std::string name) {
	windowName = name;
}

void Application::runLoop()
{
	sf::Clock deltaTimer;

	while (true) {
		auto deltaTime = deltaTimer.restart();

		m_player.handleInput(m_context->window);
		m_player.update(deltaTime.asSeconds());
		m_camera.update();

		m_quadRenderer.add({ 0, 0, 0 });

		glClearColor(0.1, 0.5, 1.0, 1.0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		m_quadRenderer.renderQuads(m_camera);

		m_context->window.display();
	}

}


void Application::handleEvents()
{
}
