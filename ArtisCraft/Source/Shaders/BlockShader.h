#include "BaseShader.h"

class BlockShader : public BaseShader {
public:
	BlockShader(std::string = "BasicVertex", std::string = "BasicFragment");

	void loadProjectionViewMatrix(glm::mat4 pvMatrix);

	void BlockShader::loadModelMatrix(glm::mat4 matrix);

private:
	virtual void getUniforms() override;

	GLuint m_locationProjectionViewMatrix;
	GLuint m_locationModelMatrix;
};