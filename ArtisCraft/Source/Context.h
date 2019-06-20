#pragma once
#include <SFML/Graphics.hpp>
#include <GL\glew.h>
#include <GLM.h>
#include <iostream>

struct RenderContext { // Creates the window and rendering context
	RenderContext(std::string windowName, unsigned int x, unsigned int y) {
		sf::ContextSettings settings;	
		settings.antialiasingLevel = 0;
		settings.minorVersion = 4;
		settings.majorVersion = 4;
		settings.depthBits = 24;
		settings.stencilBits = 8;

		window.create(sf::VideoMode(1920, 1080), windowName, sf::Style::None, settings);

		glewInit();
		glGetError();
		glewExperimental = GL_TRUE;
		glViewport(0, 0, x, y);

		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		window.setFramerateLimit(60);
	};

	sf::RenderWindow window;
};