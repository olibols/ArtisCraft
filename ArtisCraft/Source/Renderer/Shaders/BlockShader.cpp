#include "BlockShader.h"

BlockShader::BlockShader(std::string vertexFile, std::string fragmentFile) : BaseShader(vertexFile, fragmentFile)
{
	getUniforms();
}

void BlockShader::loadProjectionViewMatrix(glm::mat4 projectionViewMatrix)
{
	loadMatrix4(m_locationProjectionViewMatrix, projectionViewMatrix);
}

void BlockShader::loadModelMatrix(glm::mat4 modelMatrix)
{
	loadMatrix4(m_locationModelMatrix, modelMatrix);
}

void BlockShader::getUniforms()
{
	useProgram();
	m_locationProjectionViewMatrix = glGetUniformLocation(programID, "projViewMatrix");
	m_locationModelMatrix = glGetUniformLocation(programID, "modelMatrix");
}
