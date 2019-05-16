#include "BlockShader.h"

BlockShader::BlockShader(std::string vertexFile, std::string fragmentFile) : BaseShader(vertexFile, fragmentFile)
{
	getUniforms();
}

void BlockShader::loadProjectionViewMatrix(glm::mat4 pvMatrix)
{
	loadMatrix4(m_locationProjectionViewMatrix, pvMatrix);
}

void BlockShader::loadModelMatrix(glm::mat4 matrix)
{
	loadMatrix4(m_locationModelMatrix, matrix);
}

void BlockShader::getUniforms() {
	useProgram();
	m_locationProjectionViewMatrix = glGetUniformLocation(m_id, "projViewMatrix");
	m_locationModelMatrix = glGetUniformLocation(m_id, "modelMatrix");
}