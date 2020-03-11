#include "WorldTerrain.h"

#include "../Chunk/Chunk.h"
#include "../Coordinates.h"
#include "StructureBuilder.h"
#include "Structures/StoneStructure.h"
#include "Structures/OakTreeStructure.h"

#include <chrono>
#include <random>

struct GenResults {
	bool shouldGen = true;
	BlockID blockType = BlockID::ERR_TYPE;
};

WorldTerrain::WorldTerrain(int seed, ChunkManager* manager) : m_mainHeightmap(seed), m_treemap(seed * 3), m_rockmap(seed * 2), m_riverMap(seed / 2), m_grassMap(seed + 3), m_chunkManager(manager)
{
	m_seed = seed;
	setupGens();
}

void WorldTerrain::setSeed(int seed)
{
	m_mainHeightmap.SetSeed(seed);
	m_treemap.SetSeed(seed * 3);
	m_rockmap.SetSeed(seed * 2);
	m_riverMap.SetSeed(seed / 2);
	m_grassMap.SetSeed(seed + 3);
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

BlockID WorldTerrain::getBlockAt(int x, int y, int z, Column* column)
{
	if (y < column->getHeight(x, z)) {
		return BlockID::Grass;
	}
	return BlockID::Air;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	double height = m_mainHeightmap.GetHeight(x, z);

	int riv = m_riverMap.GetHeight(x, z);

	if (riv < 190 && riv > 185) {
		height -= 5;
	}

	return height;
}

int random(int n) {
	n = (n >> 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return nn;
}

void WorldTerrain::buildChunk(Chunk* chunk)
{
	if (!chunk->isLoaded()) {

		auto& column = m_chunkManager->addColumn({ chunk->getLocation().x, chunk->getLocation().z });
		genHeightmap(&column, chunk->getLocation());
		genBlockmap(&column, chunk->getLocation());

		auto cp = chunk->getLocation();

		if (!shouldBuild(chunk, &column)) { chunk->setLoaded(); return; }
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				int height = column.getHeight(x, z);
				for (int y = 0; (cp.y * CHUNK_SIZE + y) <= height && y < CHUNK_SIZE; y++) {
					auto wPos = toGlobalBlockPos({ x,y,z }, cp);
					BlockID block = column.getBlock(x, z);
					chunk->setBlock(x, y, z, block);

					if((cp.y * CHUNK_SIZE + y) == height){
						double treeBias = m_treemap.GetHeight1_0(wPos.x, wPos.z);
						double rockBias = m_rockmap.GetHeight1_0(wPos.x, wPos.z);
						if (treeBias == 1.0 && block != BlockID::Water) {
							chunk->getSeedData().treePositions.push_back({ x, y + 1, z });
						}
						if (rockBias == 1.0) {
							chunk->getSeedData().rockPositions.push_back({ x,y,z });
						}

						if (m_grassMap.GetHeight1_0(wPos.x, wPos.z) < 0.15) {
							srand(time(NULL) * x * y * z);
							if (rand() % 100 < 85) {
								chunk->setBlock(x, y, z, BlockID::Darkgrass);
							}
						}
						srand(time(NULL) * wPos.x * y * wPos.z);
						if (rand() % 100 < 3) {
							chunk->setBlock(x, y + 1, z, BlockID::Darkleaf);
						}
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
		StructureBuilder builder;

		for (auto& pos : chunk->getSeedData().treePositions) {
			OakTreeStructure structure;
			structure.build(builder, pos);
		}
		chunk->getSeedData().treePositions.clear();

		for (auto& pos : chunk->getSeedData().rockPositions) {
			StoneStructure structure;
			structure.build(builder, pos);
		}
		chunk->getSeedData().rockPositions.clear();

		builder.build(chunk);
	}
	chunk->setSeeded();
}

void WorldTerrain::setupGens()
{
	m_mainHeightmap.SetAmplitude(400);
	m_mainHeightmap.SetOffset(-200);
	m_mainHeightmap.GetNoise().SetFrequency(0.0005);
	m_mainHeightmap.GetNoise().SetFractalLacunarity(2.0);
	
	m_riverMap.SetAmplitude(400 * 2);
	m_riverMap.SetOffset(-200);
	m_riverMap.GetNoise().SetFractalOctaves(4);
	m_riverMap.GetNoise().SetFrequency(0.0005);
	m_riverMap.GetNoise().SetFractalLacunarity(2.0);

	m_treemap.GetNoise().SetFrequency(3);
	m_treemap.GetNoise().SetNoiseType(FastNoise::NoiseType::Value);
	m_rockmap.GetNoise().SetFrequency(0.2);
	m_rockmap.GetNoise().SetNoiseType(FastNoise::NoiseType::Value);

	m_grassMap.GetNoise().SetFrequency(0.01);
	m_grassMap.GetNoise().SetNoiseType(FastNoise::NoiseType::Simplex);
}

void WorldTerrain::genHeightmap(Column* column, sf::Vector3i worldPos)
{
	if (column->isHeightsLoaded()) return;

	HeightMap heights;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			auto nx = worldPos.x * CHUNK_SIZE + x;
			auto nz = worldPos.z * CHUNK_SIZE + z;
			heights[x][z] = getHeightAt(nx, nz);
		}
	}
	column->setHeights(heights);
	column->setHeightsLoaded();
}

void WorldTerrain::genBlockmap(Column * column, sf::Vector3i worldPos)
{
	if (column->isBlocksLoaded()) return;

	BlockMap blocks;

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			auto nx = worldPos.x * CHUNK_SIZE + x;
			auto nz = worldPos.z * CHUNK_SIZE + z;

			int riv = m_riverMap.GetHeight(nx, nz);

			if (riv < 190 && riv > 185) {
				blocks[x][z] = BlockID::Water;
			}
			else {
				blocks[x][z] = BlockID::Grass;
			}
		}
	}
	column->setBlocks(blocks);
	column->setBlocksLoaded();
}

bool WorldTerrain::shouldBuild(Chunk * chunk, Column* column)
{
	int height = column->getHeight(0, 0);
	sf::Vector3i pos = chunk->getLocation() * CHUNK_SIZE;

	if (pos.y > height + CHUNK_SIZE) {
		return false;
	}


	return true;
}
