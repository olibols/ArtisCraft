#include "ShaderProgram.h"
#include "LoadShader.h"

ShaderProgram::ShaderProgram(std::string vertex, std::string fragment)
{
	_ID = loadShaders(vertex, fragment);
	glUseProgram(_ID);
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

void ShaderProgram::loadInt(GLuint location, int value)
{
	glUniform1i(location, value);
}

void ShaderProgram::loadFloat(GLuint location, float value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector2(GLuint location, glm::vec2 vect)
{
	glUniform2f(location, vect.x, vect.y);
}

void ShaderProgram::loadVector3(GLuint location, glm::vec3 vect)
{
	glUniform3f(location, vect.x, vect.y, vect.z);
}

void ShaderProgram::loadVector4(GLuint location, glm::vec4 vect)
{
	glUniform4f(location, vect.x, vect.y, vect.z, vect.w);
}

void ShaderProgram::loadMatrix4(GLuint location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
