#include <vector>
#include <GLM.h>

#include "../Shaders/BlockShader.h"
#include "../Texture/BasicTexture.h"
#include "../../Model/Model.h"

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
	BasicTexture m_texture;
};