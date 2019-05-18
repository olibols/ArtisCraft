#include <vector>
#include <map>
#include <Model/GameObject.h>
#include <Texture/BasicTexture.h>

class Model : public GameObject{
public:
	Model();
	virtual ~Model();

	virtual void draw() override;
	virtual void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
	virtual void update() override;
	virtual void setProgram(GLuint shaderID) override;
	virtual void destroy() override;

	virtual GLuint getVao() override;
	virtual std::vector<GLuint> getVBOs() override;

	virtual BasicTexture getTexture(std::string textureName) override;
	virtual void setTexture(std::string textureName, BasicTexture textureID) override;

protected:

	GLuint vaoID;
	GLuint programID;
	std::vector<GLuint> VBOs;
	std::map<std::string, BasicTexture> textures;
};