#include "WorldTerrain.h"

#include "../Chunk/Chunk.h"
#include "../Coordinates.h"
#include "StructureBuilder.h"

#include <random>

struct GenResults {
	bool shouldGen = true;
	BlockID blockType = BlockID::ERR_TYPE;
};

WorldTerrain::WorldTerrain(int seed, ChunkManager* manager) : m_mainHeightmap(seed), m_mountainHeightmap(seed * 3), m_chunkManager(manager)
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
	sf::Vector3i chunkPos = toChunkPos({ x,y,z });
	sf::Vector3i localPos = toLocalBlockPos({ x,y,z });

	if (y < m_chunkManager->addColumn({ chunkPos.x, chunkPos.z }).getHeight(localPos.x, localPos.z)) {
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
	genHeightmap(&m_chunkManager->addColumn({ chunk->getLocation().x, chunk->getLocation().z }), { chunk->getLocation().x, chunk->getLocation().z });

	if (!chunk->isLoaded()) {
		if (!shouldBuild(chunk)) { chunk->setLoaded(); return; }
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				for (int x = 0; x < CHUNK_SIZE; x++) {
					auto globalpos = toGlobalBlockPos({ x,y,z }, chunk->getLocation());
					BlockID block = getBlockAt(globalpos.x, globalpos.y, globalpos.z);
					if (block == BlockID::Air) break;
					chunk->setBlock(x, y, z, block);
				}
			}
		}
	}	
	chunk->setLoaded();
}

void WorldTerrain::seedChunk(Chunk* chunk)
{
	if (!chunk->isSeeded()) {
		StructureBuilder builder;

		for (auto& pos : m_treePositions) {
			builder.addBlock(pos.x, pos.y, pos.z, BlockID::Sand);
		}
		m_treePositions.clear();
		builder.build(chunk);
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

void WorldTerrain::genHeightmap(Column* column, sf::Vector2i worldPos)
{
	if (column->isLoaded()) return;

	HeightMap heights;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			auto pos = toGlobalBlockPos({ x,0,z }, { worldPos.x, 0, worldPos.y });
			heights[x][z] = getHeightAt(pos.x, pos.z);
		}
	}
	column->setHeights(heights);
	column->setLoaded();
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
