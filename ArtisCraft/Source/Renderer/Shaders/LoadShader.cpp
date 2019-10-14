#include "LoadShader.h"
#include <vector>
#include "../Util/FileUtilities.h"

GLuint compileShader(const GLchar *source, GLenum shaderType) {
	GLuint shaderID = glCreateShader(shaderType); // Create a shader object within opengls memory and assign its ID to shaderID

	glShaderSource(shaderID, 1, &source, nullptr); // Give the previously made shader the source code we input
	glCompileShader(shaderID); // Compile the source for the shader

	GLint isSuccess = 0;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess); // Get the compile log for the shader
	if (!isSuccess)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		for (std::vector<char>::const_iterator i = errorLog.begin(); i != errorLog.end(); ++i)
			printf(i._Ptr);
	}

	return shaderID;
}

GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID) { // Link the two shaders into a program
	GLuint programID = glCreateProgram();

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);

	return programID;
}

GLuint loadShaders(std::string vertexShader, std::string fragmentShader) {
	std::string vertexSource = FileUtil::getContents("../Shaders/" + vertexShader + ".glsl");
	std::string fragmentSource = FileUtil::getContents("../Shaders/" + fragmentShader + ".glsl");

	GLuint vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

	GLuint shaderID = linkProgram(vertexShaderID, fragmentShaderID); // The final linked shader program ID

	glDeleteShader(vertexShaderID); // Delete the shaders for memory purposes
	glDeleteShader(fragmentShaderID); // ^

	return shaderID;
}