#pragma once
#include "Shaders/BlockShader.h"
#include "../Model.h"
#include "../Camera.h"
#include "Texture/BasicTexture.h"

class QuadRenderer {
public:
	QuadRenderer();

	void addQuad(glm::vec3 pos);

	void renderQuads(Camera& cam);
private:

	Mesh _quadMesh;

	std::vector<glm::vec3> _quads;

	BlockShader* _shader = nullptr;

	Model* _quadModel = nullptr;

	BasicTexture* _texture = nullptr;
};