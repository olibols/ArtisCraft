#pragma once
#include <GLM.h>
#include <SFML/Graphics.hpp>

#include "../Camera.h"
#include "../World/Chunk/Chunk.h"

#include "ChunkRenderer.h"
#include "SFMLRenderer.h"
#include "CubeRenderer.h"
#include "ParticleRenderer.h"


class RenderMaster {
public:
	void drawCube(glm::vec3 position);
	void drawChunk(ChunkMesh & chunkMesh);
	void drawSFML(sf::Drawable& drawable);
	void addParticle(BaseParticle& particle);

	void finishRender(sf::RenderWindow& window, Camera& camera);

private:
	sf::Clock clok;
	CubeRenderer _cubeRenderer;
	ChunkRenderer _chunkRenderer;
	SFMLRenderer _SFMLRenderer;
	ParticleRenderer _particleRenderer;
};