#include "Application.h"

Application::Application(std::string windowName)
{
	m_pContext = new RenderContext("ArtisCraft", Settings::width, Settings::height);
	m_pCamera = new Camera();
	m_pPlayer = new Player();

	m_pShader = new MainShader();

	m_pContext->window.setMouseCursorVisible(false);
}

void Application::runLoop()
{
	m_pCamera->hookEntity(*m_pPlayer);

	sf::Clock timer;
	sf::Clock dtTimer;

	GLuint VAO;
	glGenBuffers(1, &VAO);
	glBindVertexArray(VAO);

	m_pShader->loadResolution(glm::vec2(1280.0, 720.0));

	while (true) {
		printf("FPS: %f \n", 1.0 / dtTimer.getElapsedTime().asSeconds());
		dtTimer.restart();

		m_pPlayer->handleInput(m_pContext->window);
		m_pPlayer->update(dtTimer.getElapsedTime().asSeconds());
		m_pCamera->update();

		m_pShader->loadPosition(m_pCamera->position);
		m_pShader->loadRotation(m_pCamera->rotation);

		//printf("Position: %f, %f, %f \n", m_pCamera->position.x, m_pCamera->position.y, m_pCamera->position.z);

		handleEvents();

		m_pShader->loadTime(timer.getElapsedTime().asSeconds());

		glClearColor(0.1, 0.5, 1.0, 1.0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

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