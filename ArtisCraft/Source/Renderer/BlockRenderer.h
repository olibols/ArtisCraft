#pragma once

#include "../Camera.h"

#include "Shaders/BlockShader.h"
#include "../GL/Model.h"

#include <vector>

class BlockRenderer {
public:
	BlockRenderer();

	void addBlock(glm::vec3 position);

	void render(Camera& cam);

private:
	BlockShader m_shader;
	std::vector<glm::vec3> m_positions;
	Model m_cubeModel;
};