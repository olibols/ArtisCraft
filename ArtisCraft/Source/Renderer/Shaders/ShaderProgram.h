#pragma once
#include "LoadShader.h"
#include <includes.h>

class ShaderProgram {
public:
	ShaderProgram(std::string vertex, std::string fragment);
	~ShaderProgram();

	void useProgram();
	void deleteProgram();

	GLuint getID() const;

	void loadInt(GLuint Location, int value);
	void loadFloat(GLuint Location, float value);
	void loadVector2(GLuint location, glm::vec2 vect);
	void loadVector3(GLuint location, glm::vec3 vect);
	void loadVector4(GLuint location, glm::vec4 vect);

	void loadMatrix4(GLuint location, const glm::mat4 matrix);

	void loadFloatArray(GLuint location, float arr[], int arrSize);

protected:

	GLuint _ID;
};