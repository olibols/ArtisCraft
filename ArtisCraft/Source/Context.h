#include <SFML/Graphics.hpp>
#include <GL\glew.h>

struct RenderContext { // Creates the window and rendering context
	RenderContext(std::string windowName, unsigned int x, unsigned int y) {
		sf::ContextSettings settings;	
		settings.antialiasingLevel = 0;
		settings.minorVersion = 3;
		settings.majorVersion = 3;
		settings.depthBits = 24;
		settings.stencilBits = 8;

		window.create({ x, y }, windowName, sf::Style::Close, settings);

		glewInit();
		glewExperimental = GL_TRUE;
		glViewport(0, 0, x, y);

		glCullFace(GL_BACK);

		window.setFramerateLimit(60);
	};

	sf::RenderWindow window;
};