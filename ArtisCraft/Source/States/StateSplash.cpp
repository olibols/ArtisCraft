#include "StateSplash.h"

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>


StateSplash::StateSplash(Application & app) : StateBase(app)
{
}

void StateSplash::update(float deltaTime)
{
}

void StateSplash::render(MasterRenderer& renderer)
{
	/*glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	sf::Font font;
	font.loadFromFile("../Resources/Fonts/rs.ttf");

	sf::Text title;
	title.setFont(font);
	title.setString("ArtisCraft");
	title.setFillColor(sf::Color::White);

	window.draw(title);*/
}

void StateSplash::handleInput(MasterRenderer& renderer)
{
}