#pragma once
#include "LoadShader.h"

class ShaderProgram {
public:
	ShaderProgram(std::string vertex, std::string fragment);
	~ShaderProgram();

	void useProgram();
	void deleteProgram();

	GLuint getID() const;

private:

	GLuint _ID;
};