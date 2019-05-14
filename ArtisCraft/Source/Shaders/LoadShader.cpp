#include "LoadShader.h"

GLuint compileShader(const GLchar *source, GLenum shaderType) {
	GLuint shaderID = glCreateShader(shaderType);

	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	GLint isSuccess = 0;
	GLchar infoLog[512];

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
	if (!isSuccess)
	{
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		printf("Unable to load shader: %s", std::string(infoLog));
	}

	return shaderID;
}

GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
	GLuint programID = glCreateProgram();

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);

	return programID;
}

GLuint loadShaders(std::string vertexShader, std::string fragmentShader) {
	std::string vertexSource = FileUtil::getContents("Shaders/" + vertexShader + ".glsl");
	std::string fragmentSource = FileUtil::getContents("Shaders/" + fragmentShader + ".glsl");

	GLuint vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

	GLuint shaderID = linkProgram(vertexShaderID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return shaderID;
}