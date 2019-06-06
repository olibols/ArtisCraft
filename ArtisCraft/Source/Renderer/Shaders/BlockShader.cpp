#include "BlockShader.h"

BlockShader::BlockShader(std::string vertexFile, std::string fragmentFile) : ShaderProgram(vertexFile, fragmentFile)
{
	getUniforms();
}

void BlockShader::loadProjViewMatrix(glm::mat4 projViewMatrix)
{
	loadMatrix4(_locProjViewMat, projViewMatrix);
}

void BlockShader::loadModelMatrix(glm::mat4 modelMatrix)
{
	loadMatrix4(_locModelMat, modelMatrix);
}

void BlockShader::getUniforms()
{
	useProgram();
	_locProjViewMat = glGetUniformLocation(_ID, "projViewMatrix");
	_locModelMat = glGetUniformLocation(_ID, "modelMatrix");
}
