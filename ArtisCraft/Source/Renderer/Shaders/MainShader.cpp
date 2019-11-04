#include "MainShader.h"

MainShader::MainShader(std::string vertexFile, std::string fragmentFile) : ShaderProgram(vertexFile, fragmentFile)
{
	getUniforms();
}

void MainShader::loadResolution(glm::vec2 resolution)
{
	loadVector2(m_locResolution, resolution);
}

void MainShader::loadTime(float time)
{
	loadFloat(m_locTime, time);
}

void MainShader::loadViewmatrix(glm::mat4 matrix)
{
	loadMatrix4(m_locViewmatrix, matrix);
}

void MainShader::loadPosition(glm::vec3 position)
{
	loadVector3(m_locPosition, position);
}

void MainShader::loadRotation(glm::vec3 rotation)
{
	loadVector3(m_locRotation, rotation);
}

void MainShader::loadPoints(glm::vec3 points[])
{

}

void MainShader::getUniforms()
{
	useProgram();
	m_locResolution = glGetUniformLocation(_ID, "iResolution");
	m_locTime = glGetUniformLocation(_ID, "iTime");
	m_locViewmatrix = glGetUniformLocation(_ID, "iViewMatrix");
	m_locPosition = glGetUniformLocation(_ID, "iPosition");
	m_locRotation = glGetUniformLocation(_ID, "iRotation");
	m_locPoints = glGetUniformLocation(_ID, "iPoints[50]");
}
