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
	void loadRotation(glm::vec3 rotation);
	void loadPixels(float arr[], int x, int y);

protected:
	void getUniforms();

	GLuint m_locResolution;
	GLuint m_locTime;
	GLuint m_locViewmatrix;
	GLuint m_locPosition;
	GLuint m_locRotation;
	GLuint m_locPixels;
};