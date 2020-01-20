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
	if (y < 0) return BlockID::Air;
	if (y < getHeightAt(x, z)) {
		return BlockID::Grass;
	}

	return BlockID::Air;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	double height = m_mainHeightmap.GetHeight(x, z);
	double mountainmod = (m_mountainHeightmap.GetRidgedHeight(x, z) + 1) * 2.0;
	return height * mountainmod;
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
					if (block != BlockID::Air) {
						chunk->setBlock(x, y, z, block);
					}
				}
			}
		}
	}
	chunk->setLoaded();
}

void WorldTerrain::seedChunk(Chunk* chunk)
{
	if (!chunk->isSeeded()) {

	}
	chunk->setSeeded();
}

void WorldTerrain::setupGens()
{
	m_mountainHeightmap.GetNoise().SetFrequency(0.0006);
	m_mountainHeightmap.GetNoise().SetFractalGain(0.5);
	m_mountainHeightmap.GetNoise().SetFractalLacunarity(5.0);
	m_mountainHeightmap.SetOffset(0);
}

bool WorldTerrain::shouldBuild(Chunk * chunk)
{
	sf::Vector3i pos = chunk->getLocation() * CHUNK_SIZE;
	if (pos.y < 0) return false;

	if (getHeightAt(pos.x, pos.z) < (pos.y - CHUNK_SIZE * 2)) {
		return false;
	}

	return true;
}
