#include "BaseShader.h"


class BlockShader : public BaseShader
{
public:
	BlockShader(std::string vertexFile = "BasicVertex", std::string fragmentFile = "BasicFragment");

	void loadProjectionViewMatrix(glm::mat4 projectionViewMatrix);
	void loadModelMatrix(glm::mat4 modelMatrix);

private:
	virtual void getUniforms() override;

	GLuint m_locationProjectionViewMatrix;
	GLuint m_locationModelMatrix;
};

