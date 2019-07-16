#pragma once
#include "Chunk/ChunkBlock.h"
#include "../Renderer/RenderMaster.h"
#include "Chunk/Region.h"
#include <Utils.h>
#include "ChunkManager.h"

#include <unordered_set>

#include <SFML/Graphics.hpp>

class World {
public:
	World();

	ChunkBlock getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, ChunkBlock block);

	void update(const Camera& camera);

	void render(RenderMaster& renderer);

private:
	
	ChunkManager _chunkManager;
	static std::unordered_set<sf::Vector3i> _changedRegions;
};