#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

struct RenderContext { // Creates the window and rendering context
	RenderContext(std::string windowName, unsigned int x, unsigned int y) {
		sf::ContextSettings settings;
		settings.antialiasingLevel = 0;
		settings.minorVersion = 4;
		settings.majorVersion = 4;
		settings.depthBits = 24;
		settings.stencilBits = 8;

		window.create(sf::VideoMode(1280, 720), windowName, sf::Style::Close, settings);

		glViewport(0, 0, x, y);

		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	};

	sf::RenderWindow window;

};