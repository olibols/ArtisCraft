#include "StatePlaying.h"

#include <SFML/OpenGL.hpp>

#include <memory>

StatePlaying::StatePlaying(Application & app) : StateBase(app)
{
}

void StatePlaying::update(float deltaTime)
{
}

void StatePlaying::render(sf::RenderWindow& window)
{
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void StatePlaying::handleInput()
{
}
