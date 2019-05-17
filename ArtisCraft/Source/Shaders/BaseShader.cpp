#include "BaseShader.h"
#include "LoadShader.h"
#include "../Util/GLM.h"

BaseShader::BaseShader(std::string& vertexFile, std::string& fragmentFile)
{
	m_id = loadShaders(vertexFile, fragmentFile); // Load the shaders
	useProgram();
}


void BaseShader::loadInt(GLuint location, int value)
{
	glUniform1i(location, value);
}

void BaseShader::loadFloat(GLuint location, int value)
{
	glUniform1f(location, value);
}

void BaseShader::loadVector2(GLuint location, glm::vec2 vect)
{
	glUniform2f(location, vect.x, vect.y);
}

void BaseShader::loadVector3(GLuint location, glm::vec3 vect)
{
	glUniform3f(location, vect.x, vect.y, vect.z);
}

void BaseShader::loadVector4(GLuint location, glm::vec4 vect)
{
	glUniform4f(location, vect.x, vect.y, vect.z, vect.w);
}

void BaseShader::loadMatrix4(GLuint location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

BaseShader::~BaseShader()
{
	glDeleteProgram(m_id);
}

void BaseShader::useProgram()
{
	glUseProgram(m_id); // Sets this shader program as the active one
}