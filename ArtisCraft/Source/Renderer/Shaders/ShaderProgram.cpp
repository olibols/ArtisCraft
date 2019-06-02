#include "ShaderProgram.h"
#include "LoadShader.h"

ShaderProgram::ShaderProgram(std::string vertex, std::string fragment)
{
	_ID = loadShaders(vertex, fragment);
}

ShaderProgram::~ShaderProgram() {
	deleteProgram();
}

void ShaderProgram::useProgram()
{
	glUseProgram(_ID);
}

void ShaderProgram::deleteProgram()
{
	glDeleteProgram(_ID);
}

GLuint ShaderProgram::getID() const
{
	return _ID;
}
