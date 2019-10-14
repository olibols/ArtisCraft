#include "Application.h"
#include "States/PlayingState.h"

Application::Application(std::string windowName)
{
	m_pContext = new RenderContext("ArtisCraft", Settings::width, Settings::height);
	m_pCamera = new Camera();

	m_pContext->window.setMouseCursorVisible(false);

	pushState<PlayingState>(*this);
}

void Application::runLoop()
{
	sf::Clock dtTimer;

	while (true) {
		auto deltaTime = dtTimer.restart();

		auto& state = *m_states.back();

		if (m_shouldUpdate) {
			state.handleInput();
		}

		state.update(deltaTime.asSeconds());

		m_pCamera->update();

		state.render(m_renderer);
		

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

			default:
				break;
			}				   

		default:
			break;
		}		
	}
}	