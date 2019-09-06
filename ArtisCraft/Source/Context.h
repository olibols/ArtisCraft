#pragma once
#include <SFML/Graphics.hpp>
#include <GL\glew.h>
#include <GLM.h>
#include <iostream>

inline void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

struct RenderContext { // Creates the window and rendering context
	RenderContext(std::string windowName, unsigned int x, unsigned int y) {
		sf::ContextSettings settings;	
		settings.antialiasingLevel = 0;
		settings.minorVersion = 4;
		settings.majorVersion = 4;
		settings.depthBits = 24;
		settings.stencilBits = 8;

		window.create(sf::VideoMode(1920, 1080), windowName, sf::Style::Close, settings);

		glewInit();
		glGetError();
		glewExperimental = GL_TRUE;
		glViewport(0, 0, x, y);

		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);

		//glEnable(GL_DEBUG_OUTPUT);
		//glDebugMessageCallback(MessageCallback, 0);

		//window.setFramerateLimit(60);
	};

	sf::RenderWindow window;
};