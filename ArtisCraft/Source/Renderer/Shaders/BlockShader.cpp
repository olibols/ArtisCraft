#include "BlockShader.h"

// Constructor
BlockShader::BlockShader(std::string vertexFile, std::string fragmentFile) : ShaderProgram(vertexFile, fragmentFile)
{
	getUniforms();
}

// Loads the projection view matrix into the shader on the gpu
void BlockShader::loadProjViewMatrix(glm::mat4 projViewMatrix)
{
	loadMatrix4(m_locProjViewMat, projViewMatrix);
}

// Loads the model matrix
void BlockShader::loadModelMatrix(glm::mat4 modelMatrix)
{
	loadMatrix4(m_locModelMat, modelMatrix);
}

// Gets the location of the glsl uniforms
void BlockShader::getUniforms()
{
	useProgram();
	m_locProjViewMat = glGetUniformLocation(m_ID, "projViewMatrix");
	m_locModelMat = glGetUniformLocation(m_ID, "modelMatrix");
}