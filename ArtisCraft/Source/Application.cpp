#include "Application.h"

Application::Application(std::string windowName)
{
	m_pContext = new RenderContext("ArtisCraft", Settings::width, Settings::height);
	//m_pCamera = new Camera();

	m_pShader = new MainShader();

	m_pContext->window.setMouseCursorVisible(false);
}



void Application::runLoop()
{
	sf::Clock dtTimer;

	GLuint VAO;
	glGenBuffers(1, &VAO);
	glBindVertexArray(VAO);

	while (true) {
		handleEvents();

		glClearColor(0.1, 0.5, 1.0, 1.0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		m_pContext->window.display();
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
				shouldUpdate = !shouldUpdate;
				m_pContext->window.setMouseCursorVisible(!shouldUpdate);
				sf::sleep(sf::Time(sf::seconds(0.2)));

			default:
				break;
			}				   

		default:
			break;
		}		
	}
}	