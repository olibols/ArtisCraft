#pragma once
#include "ShaderProgram.h"
#include <includes.h>

class MainShader : public ShaderProgram {
public:
	MainShader(std::string vertexFile = "BasicVertex", std::string fragmentFile = "BasicFragment");

	void loadResolution(glm::vec2 resolution);
	void loadTime(float time);

protected:
	void getUniforms();

	GLuint m_locResolution;
	GLuint m_locTime;
};