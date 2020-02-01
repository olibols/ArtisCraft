#include "WorldTerrain.h"

#include "../Chunk/Chunk.h"
#include "../Coordinates.h"
#include "StructureBuilder.h"

#include <chrono>
#include <random>

struct GenResults {
	bool shouldGen = true;
	BlockID blockType = BlockID::ERR_TYPE;
};

WorldTerrain::WorldTerrain(int seed, ChunkManager* manager) : m_mainHeightmap(seed), m_treemap(seed * 3), m_chunkManager(manager)
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
	return height;
}

void WorldTerrain::buildChunk(Chunk* chunk)
{
	if (!chunk->isLoaded()) {

		auto& column = m_chunkManager->addColumn({ chunk->getLocation().x, chunk->getLocation().z });
		genHeightmap(&column, chunk->getLocation());

		auto cp = chunk->getLocation();

		if (!shouldBuild(chunk, &column)) { chunk->setLoaded(); return; }
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				int height = column.getHeight(x, z);
				for (int y = 0; (cp.y * CHUNK_SIZE + y) <= height && y < CHUNK_SIZE; y++) {
					auto wPos = toGlobalBlockPos({ x,y,z }, cp);
					chunk->setBlock(x, y, z, BlockID::Grass);

					if((cp.y * CHUNK_SIZE + y) == height){
						auto seed = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
						srand(seed * x * z);
						if (rand() % 1000 > 995) {
							chunk->getSeedData().treePositions.push_back({ x, y + 1, z });
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
			builder.fill(pos.x-1, pos.z-1, pos.y, pos.x + 1, pos.z + 1, BlockID::Wood);
			builder.fill(pos.x-1, pos.z-1, pos.y + 1, pos.x + 1, pos.z + 1, BlockID::Wood);
			builder.fill(pos.x-1, pos.z-1, pos.y + 2, pos.x + 1, pos.z + 1, BlockID::Wood);
			builder.fill(pos.x-1, pos.z-1, pos.y + 3, pos.x + 1, pos.z + 1, BlockID::Wood);
			builder.fill(pos.x-1, pos.z-1, pos.y + 4, pos.x + 1, pos.z + 1, BlockID::Wood);
			builder.fill(pos.x-1, pos.z-1, pos.y + 5, pos.x + 1, pos.z + 1, BlockID::Wood);
			builder.fill(pos.x-1, pos.z-1, pos.y + 6, pos.x + 1, pos.z + 1, BlockID::Wood);
			builder.fill(pos.x-1, pos.z-1, pos.y + 7, pos.x + 1, pos.z + 1, BlockID::Wood);
			builder.fill(pos.x-1, pos.z-1, pos.y + 8, pos.x + 1, pos.z + 1, BlockID::Wood);
		}
		chunk->getSeedData().treePositions.clear();
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
}

void WorldTerrain::genHeightmap(Column* column, sf::Vector3i worldPos)
{
	if (column->isLoaded()) return;

	HeightMap heights;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			auto nx = worldPos.x * CHUNK_SIZE + x;
			auto nz = worldPos.z * CHUNK_SIZE + z;
			heights[x][z] = getHeightAt(nx, nz);
		}
	}
	column->setHeights(heights);
	column->setLoaded();
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
