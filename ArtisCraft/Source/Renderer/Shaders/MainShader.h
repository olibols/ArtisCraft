#pragma once
#include "ShaderProgram.h"
#include <includes.h>

class MainShader : public ShaderProgram {
public:
	MainShader(std::string vertexFile = "BasicVertex", std::string fragmentFile = "BasicFragment");

	void loadResolution(glm::vec2 resolution);
	void loadTime(float time);
	void loadViewmatrix(glm::mat4 matrix);
	void loadPosition(glm::vec3 position);

protected:
	void getUniforms();

	GLuint m_locResolution;
	GLuint m_locTime;
	GLuint m_locViewmatrix;
	GLuint m_locPosition;
};