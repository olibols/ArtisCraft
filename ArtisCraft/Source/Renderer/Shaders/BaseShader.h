#include <string>
#include <GL\glew.h>
#include "../Util/GLM.h"

class BaseShader { // The basic class that other shader classes inherit.	
public:
	BaseShader(std::string vertexFile, std::string fragmentFile); // Takes in the filepath of the two shaders as the constructor
	~BaseShader();

	void useProgram(); // Binds this shader as the active shader

	void loadInt(GLuint Location, int value); // These 5 lines load values from the shader program into a value
	void loadFloat(GLuint Location, int value);
	void loadVector2(GLuint location, glm::vec2 vect);
	void loadVector3(GLuint location, glm::vec3 vect);
	void loadVector4(GLuint location, glm::vec4 vect);

	void loadMatrix4(GLuint location, const glm::mat4 matrix);
protected:
	virtual void getUniforms() = 0;
	GLuint programID;

};