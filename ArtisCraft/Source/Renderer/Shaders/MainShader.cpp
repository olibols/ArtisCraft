#include "MainShader.h"

MainShader::MainShader(std::string vertexFile, std::string fragmentFile) : ShaderProgram(vertexFile, fragmentFile)
{
	getUniforms();
}

void MainShader::loadProjViewMatrix(glm::mat4 projViewMatrix)
{
	loadMatrix4(m_locProjViewMat, projViewMatrix);
}

void MainShader::loadModelMatrix(glm::mat4 modelMatrix)
{
	loadMatrix4(m_locModelMat, modelMatrix);
}

void MainShader::getUniforms()
{
	useProgram();
	m_locProjViewMat = glGetUniformLocation(_ID, "projViewMatrix");
	m_locModelMat = glGetUniformLocation(_ID, "modelMatrix");
}
