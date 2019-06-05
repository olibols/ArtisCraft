#pragma once
#include "../Model.h"
#include "Shaders/BlockShader.h"
#include "Texture/BasicTexture.h"

class Camera;

class QuadRenderer {
public:
	QuadRenderer();

	void addQuad(const glm::vec3 pos);

	void render(const Camera& camera);

private:

	std::vector<glm::vec3> _quads;

	Model* _quadModel = nullptr;

	BlockShader* _shader = nullptr;

	BasicTexture* _texture = nullptr;
};