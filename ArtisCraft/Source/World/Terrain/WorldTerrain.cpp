#include "WorldTerrain.h"

#include "../Chunk/Chunk.h"
#include "../Coordinates.h"

struct GenResults {
	bool shouldGen = true;
	BlockID blockType = BlockID::ERR_TYPE;
};

WorldTerrain::WorldTerrain(int seed) : m_mainHeightmap(seed), m_mountainHeightmap(seed * 3)
{
	m_seed = seed;
	setupGens();
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
	if (y < getHeightAt(x, z)) {
		return BlockID::Grass;
	}

	return BlockID::Air;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	return m_mainHeightmap.GetHeight(x, z) * (m_mountainHeightmap.GetHeight1_0(x,z) + 1.0);
}

void WorldTerrain::buildChunk(Chunk* chunk)
{
	if (!chunk->isLoaded()) {
		if (!shouldBuild(chunk)) { chunk->setLoaded(); return; }
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

void WorldTerrain::setupGens()
{
	m_mountainHeightmap.GetNoise().SetFrequency(0.001);
	m_mountainHeightmap.GetNoise().SetFractalGain(2);
}

bool WorldTerrain::shouldBuild(Chunk * chunk)
{
	sf::Vector3i pos = chunk->getLocation() * CHUNK_SIZE;
	if (pos.y < m_mainHeightmap.GetHeight(pos.x, pos.z) - CHUNK_SIZE * 2){
		return false;
	}
	return true;
}
