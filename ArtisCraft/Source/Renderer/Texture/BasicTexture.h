#pragma once
#include <string>
#include <GL\glew.h>

class BasicTexture
{
public:
	BasicTexture() = default;
	BasicTexture(std::string filename);

	~BasicTexture();

	void loadFromFile(std::string filename);

	void bindTexture();

private:
	GLuint textureID;
};
