#pragma once

#include "../World/Chunk/ChunkMesh.h"
#include "../Camera.h"
#include "Shaders/ChunkShader.h"

class ChunkRenderer {
public:
	void addChunk(ChunkMesh& chunk);
	void render(Camera& cam);
	void clearChunks();
private:
	std::vector<ChunkMesh*> m_chunks;

	ChunkShader m_shader;
};