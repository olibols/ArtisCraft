#include <GL\glew.h>
#include "..\Util\FileUtilities.h"

GLuint compileShader(const GLchar *source, GLenum shaderType);

GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID);

GLuint loadShaders(std::string vertexShader, std::string fragmentShader);