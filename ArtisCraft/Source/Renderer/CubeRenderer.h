#pragma once
#include "Shaders/BlockShader.h"
#include "../Model.h"
#include "../Camera.h"
#include "Texture/BasicTexture.h"
#include "Texture/TextureAtlas.h"

class CubeRenderer {
public:
	CubeRenderer();

	void addCube(glm::vec3 pos);

	void renderCubes(Camera& cam);
private:

	Mesh _cubeMesh;

	std::vector<glm::vec3> _quads;

	BlockShader* _shader = nullptr;

	Model* _cubeModel = nullptr;

	BasicTexture* _texture = nullptr;

	TextureAtlas _atlas;
};