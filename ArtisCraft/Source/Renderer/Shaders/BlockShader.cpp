#include "BlockShader.h"

BlockShader::BlockShader(std::string vertexFile, std::string fragmentFile) : ShaderProgram(vertexFile, fragmentFile)
{
	getUniforms();
}

void BlockShader::loadProjViewMatrix(glm::mat4 projViewMatrix)
{
	loadMatrix4(_locationProjViewMatrix, projViewMatrix);
}

void BlockShader::loadModelMatrix(glm::mat4 modelMatrix)
{
	loadMatrix4(_locationModelMatrix, modelMatrix);
}

void BlockShader::getUniforms()
{
	useProgram();
	_locationProjViewMatrix = glGetUniformLocation(_ID, "projViewMatrix");
	_locationModelMatrix = glGetUniformLocation(_ID, "modelMatrix");
}
