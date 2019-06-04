#pragma once
#include <string>
#include <GL\glew.h>
#include <SFML/Graphics.hpp>

class BasicTexture
{
public:
	BasicTexture() = default;
	BasicTexture(std::string filename);

	~BasicTexture();

	void loadFromFile(std::string filename);

	void bindTexture();

private:
	GLuint _ID;
};
