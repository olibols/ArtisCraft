#include "WorldTerrain.h"

#include "../Chunk/Chunk.h"
#include "../Coordinates.h"

struct GenResults {
	bool shouldGen = true;
	BlockID blockType = BlockID::ERR_TYPE;
};

WorldTerrain::WorldTerrain(int seed) : m_mainHeightmap(seed)
{
	m_seed = seed;
}

void fillChunk(Chunk* chunk, BlockID block)
{
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				chunk->setBlock(x, y, z, block);
			}
		}
	}
}

BlockID WorldTerrain::getBlockAt(int x, int y, int z)
{
	if (y < m_mainHeightmap.GetHeight(x, z)) {
		return BlockID::Grass;
	}

	return BlockID::Air;
}

void WorldTerrain::buildChunk(Chunk* chunk)
{
	if (!chunk->isLoaded()) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				for (int x = 0; x < CHUNK_SIZE; x++) {
					sf::Vector3i worldPos = toGlobalBlockPos({ x, y, z }, chunk->getLocation());
					BlockID block = getBlockAt(worldPos.x, worldPos.y, worldPos.z);
					if (block == BlockID::Air) break;
					chunk->setBlock(x, y, z, block);
				}
			}
		}
	}
	chunk->setLoaded();
}