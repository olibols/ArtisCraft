#include <string>
#include <GL\glew.h>
#include "../Util/GLM.h"

class BaseShader {
public:
	BaseShader(std::string& vertexFile, std::string& fragmentFile);
	~BaseShader();

	void useProgram();

	void loadInt(GLuint Location, int value);
	void loadFloat(GLuint Location, int value);
	void loadVector2(GLuint location, glm::vec2 vect);
	void loadVector3(GLuint location, glm::vec3 vect);
	void loadVector4(GLuint location, glm::vec4 vect);

	void loadMatrix4(GLuint location, const glm::mat4 matrix);
protected:
	virtual void getUniforms() = 0;
	GLuint m_id;

};