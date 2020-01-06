#pragma once

#include "BlockRenderer.h"
#include "ChunkRenderer.h"

#include <SFML/Graphics.hpp>
#include <glm.hpp>

class MasterRenderer {
public:
	void drawBlock(glm::vec3 pos);
	void drawChunk(ChunkMesh& chunk);

	void finishRender(sf::RenderWindow & window, Camera & camera);

private:
	BlockRenderer m_blockRenderer;
	ChunkRenderer m_chunkRenderer;
};