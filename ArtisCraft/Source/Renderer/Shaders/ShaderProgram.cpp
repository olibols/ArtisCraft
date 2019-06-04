#include "ShaderProgram.h"
#include "LoadShader.h"

ShaderProgram::ShaderProgram(std::string vertex, std::string fragment)
{
	glEnable(GL_TEXTURE_2D);
	_ID = loadShaders(vertex, fragment);
	glUniform1i(glGetUniformLocation(_ID, "myTexture"), 0);

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
