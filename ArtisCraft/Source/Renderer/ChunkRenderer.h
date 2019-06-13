#pragma once
#include <vector>
#include "Shaders/BlockShader.h"

class ChunkMesh;
class Camera;

class ChunkRenderer {
public:
	void add(ChunkMesh mesh);
	void render(Camera& camera);

private:
	std::vector<ChunkMesh> _chunks;

	BlockShader _shader;
};