#include <vector>
#include "../Util/GLM.h"
#include "../Model.h"
#include "../Texture/BaseTexture.h"
#include "../Shaders/BlockShader.h"
#include "../Camera.h"

class Camera;

class QuadRenderer {
public:
	QuadRenderer();

	void add(glm::vec3 position);

	void renderQuads(Camera camera);

private:
	std::vector<glm::vec3> m_quads;

	Model m_quadModel;
	BlockShader m_shader;
	BaseTexture m_basicTexture;

};