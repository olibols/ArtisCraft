#include <vector>
#include <GL/glew.h>
#include <GLM.h>
#include <Texture/BasicTexture.h>
#include <Shaders/BaseShader.h>

class GameObject {
public:
	virtual ~GameObject() = 0;

	virtual void draw() = 0;
	virtual void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) = 0;
	virtual void update() = 0;
	virtual void setProgram(GLuint shaderID) = 0;
	virtual void destroy() = 0;

	virtual GLuint getVao() = 0;
	virtual std::vector<GLuint> getVBOs() = 0;

	virtual void setTexture(std::string textureName, BasicTexture texture) = 0;
	virtual BasicTexture getTexture(std::string textureName) = 0;
};