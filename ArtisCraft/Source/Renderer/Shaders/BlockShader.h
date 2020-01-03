#pragma once
#include "ShaderProgram.h"

class BlockShader : public ShaderProgram {
public:
	BlockShader(std::string vertexFile = "BasicVertex", std::string fragmentFile = "BasicFragment");

	void loadProjViewMatrix(glm::mat4 projViewMatrix);
	void loadModelMatrix(glm::mat4 modelMatrix);

protected:
	void getUniforms();

	GLuint m_locProjViewMat;
	GLuint m_locModelMat;
};