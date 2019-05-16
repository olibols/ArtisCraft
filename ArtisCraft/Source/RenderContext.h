#include <SFML/Graphics.hpp>
#include <GL\glew.h>

struct RenderContext {
	RenderContext() {
		sf::ContextSettings settings;
		settings.antialiasingLevel = 0;
		settings.minorVersion = 3;
		settings.majorVersion = 3;
		settings.depthBits = 24;
		settings.stencilBits = 8;

		window.create({ 1280, 720 }, "ArtisCraft", sf::Style::Close, settings);

		glewInit();
		glewExperimental = GL_TRUE;
		glViewport(0, 0, 1280, 720);

		window.setFramerateLimit(60);
	};

	sf::RenderWindow window;
};