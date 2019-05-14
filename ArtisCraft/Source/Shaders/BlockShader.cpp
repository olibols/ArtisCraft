#include "BlockShader.h"

BlockShader::BlockShader(std::string vertexFile, std::string fragmentFile) : BaseShader(vertexFile, fragmentFile) {}

void BlockShader::loadProjectionViewMatrix(glm::mat4 pvMatrix)
{
	loadMatrix4(m_locationProjectionViewMatrix, pvMatrix);
}

void BlockShader::getUniforms() {
	m_locationProjectionViewMatrix = glGetUniformLocation(m_id, "projViewMat");
}