#pragma once
#include <GLM.h>
#include <SFML/Graphics.hpp>
#include "../Camera.h"
#include "ChunkRenderer.h"
#include "CubeRenderer.h"
#include "../World/Chunk/Chunk.h"

class RenderMaster {
public:
	void drawCube(glm::vec3 position);
	void drawChunk(ChunkMesh& mesh);

	void finishRender(sf::RenderWindow& window, Camera& camera);

private:
	CubeRenderer _cubeRenderer;

	ChunkRenderer _chunkRenderer;
};