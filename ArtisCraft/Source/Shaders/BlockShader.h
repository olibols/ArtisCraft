#include "BaseShader.h"

class BlockShader : public BaseShader {
public:
	BlockShader(std::string = "BasicVertex", std::string = "BasicFragment");

	void loadProjectionViewMatrix(glm::mat4 pvMatrix);

private:
	virtual void getUniforms() override;

	GLuint m_locationProjectionViewMatrix;
};