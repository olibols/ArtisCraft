#include "Application.h"
#include "States/StatePlaying.h"
#include "States/StateSplash.h"

#include <stdio.h>

Application::Application(std::string windowName)
{
	m_context = new RenderContext(windowName, 1280, 720);

	m_currentState = "PlayingState";
}

void Application::runLoop()
{
	std::string key = "PlayingState";
	m_states.insert(std::pair<std::string, std::unique_ptr<StatePlaying>>(key, std::make_unique<StatePlaying>(*this)));
	
	key = "SplashState";
	m_states.insert(std::pair<std::string, std::unique_ptr<StateSplash>>(key, std::make_unique<StateSplash>(*this)));

	while (true) {
		handleWindowEvents();

		StateMap::iterator it = m_states.find(m_currentState);
		if (it != m_states.end()) {
			it->second->render();
		}


		m_context->window.display();
	}
}

StateBase & Application::getState(std::string str)
{
	return *m_states[str];
}

void Application::handleWindowEvents()
{

	sf::Event e;
	while (m_context->window.pollEvent(e)) {
		switch (e.type) {
		case sf::Event::Closed:
			m_context->window.close();

		case sf::Event::KeyPressed:
			switch (e.key.code) {
			case sf::Keyboard::Escape:
				if (m_currentState == "PlayingState") m_currentState = "SplashState";
				else m_currentState = "PlayingState";
			}
		}
	}
}
