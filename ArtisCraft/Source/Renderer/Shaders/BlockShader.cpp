#include "BlockShader.h"

BlockShader::BlockShader(std::string vertexFile, std::string fragmentFile) : ShaderProgram(vertexFile, fragmentFile)
{
	getUniforms();
}

void BlockShader::loadProjViewMatrix(glm::mat4 projViewMatrix)
{
	loadMatrix4(m_locProjViewMat, projViewMatrix);
}

void BlockShader::loadModelMatrix(glm::mat4 modelMatrix)
{
	loadMatrix4(m_locModelMat, modelMatrix);
}

void BlockShader::getUniforms()
{
	useProgram();
	m_locProjViewMat = glGetUniformLocation(m_ID, "projViewMatrix");
	m_locModelMat = glGetUniformLocation(m_ID, "modelMatrix");
}