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

void MainShader::getUniforms()
{
	useProgram();
	m_locResolution = glGetUniformLocation(_ID, "iResolution");
	m_locTime = glGetUniformLocation(_ID, "iTime");
}
