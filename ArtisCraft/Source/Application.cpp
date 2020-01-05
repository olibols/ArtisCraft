#include "Application.h"
#include "States/StatePlaying.h"
#include "States/StateSplash.h"

#include <stdio.h>

Application::Application(std::string windowName) : m_context("ArtisCraft", 1280, 720)
{
	m_currentState = "PlayingState";

	glEnable(GL_DEPTH_TEST);
}

void Application::runLoop()
{
	std::string key = "PlayingState";
	m_states.insert(std::pair<std::string, std::unique_ptr<StatePlaying>>(key, std::make_unique<StatePlaying>(*this)));

	sf::Clock dtTimer;

	std::unique_ptr<StateBase>& currentState = m_states["PlayingState"];

	while (true) {
		auto deltaTime = dtTimer.restart();

		handleWindowEvents();

		currentState->handleInput(m_renderer);
		currentState->update(deltaTime.asSeconds());

		m_camera.update();

		currentState->render(m_renderer);
	}
}

StateBase & Application::getState(std::string str)
{
	return *m_states[str];
}

void Application::switchState(std::string str)
{
	m_currentState = str;
}

void Application::handleWindowEvents()
{

	sf::Event e;
	while (m_context.window.pollEvent(e)) {
		switch (e.type) {
		case sf::Event::Closed:
			m_context.window.close();

		case sf::Event::KeyPressed:
			switch (e.key.code) {
			case sf::Keyboard::Escape:
				if (m_currentState == "PlayingState") m_currentState = "SplashState";
				else m_currentState = "PlayingState";
			}
		}
	}
}
