#pragma once
#include "ShaderProgram.h"

class BlockShader : public ShaderProgram {
public:
	BlockShader(std::string = "BasicVertex", std::string = "BasicFragment");

	void loadProjViewMatrix(glm::mat4 projViewMatrix);

	void loadModelMatrix(glm::mat4 modelMatrix);
private:
	void getUniforms();

	GLuint _locationProjViewMatrix;
	GLuint _locationModelMatrix;

};