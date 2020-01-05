#pragma once

#include "../World/Chunk/Chunk.h"
#include "../Camera.h"
#include "Shaders/ChunkShader.h"

class ChunkRenderer {
public:
	void addChunk(Chunk chunk);
	void render(Camera& cam);
private:
	std::vector<Chunk> m_chunks;

	ChunkShader m_shader;
};