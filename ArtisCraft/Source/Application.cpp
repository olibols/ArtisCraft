#include "Application.h"

Application::Application(std::string windowName)
{
	m_pContext = new RenderContext("ArtisCraft", Settings::width, Settings::height);
	m_pCamera = new Camera();

	m_pContext->window.setMouseCursorVisible(false);
}

void Application::runLoop()
{
	sf::Clock dtTimer;

	while (true) {
		auto deltaTime = dtTimer.restart();
		
		m_pCamera->update();

		handleEvents();
	}
}


void Application::handleEvents()
{
	sf::Event e;
	while (m_pContext->window.pollEvent(e)) {
		switch (e.type) {

		case sf::Event::Closed:
			m_pContext->window.close();

		case sf::Event::KeyPressed:
			switch (e.key.code) {
			case sf::Keyboard::Escape:
				m_shouldUpdate = !m_shouldUpdate;
				m_pContext->window.setMouseCursorVisible(!m_shouldUpdate);
				sf::sleep(sf::Time(sf::seconds(0.2)));

			default:
				break;
			}				   

		default:
			break;
		}		
	}
}	