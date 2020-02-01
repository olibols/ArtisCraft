#pragma once

#include "../BlockID.h"
#include "Generators/NoiseWrapper.h"
#include "Column.h"
#include "../Coordinates.h"
#include "../ChunkManager.h"

class Chunk;
struct GenResults;

class WorldTerrain {
public:
	WorldTerrain(int seed, ChunkManager* manager);

	BlockID getBlockAt(int x, int y, int z, Column* column);
	int getHeightAt(int x, int z);

	void buildChunk(Chunk* chunk);
	void seedChunk(Chunk* chunk);

private:
	void setupGens();
	void genHeightmap(Column* column, sf::Vector3i worldPos);
	ChunkManager* m_chunkManager;

	NoiseWrapper m_mainHeightmap;
	NoiseWrapper m_treemap;
	NoiseWrapper m_rockmap;

	int m_seed;
	
	std::vector<sf::Vector3i> m_treePositions;
	
	bool shouldBuild(Chunk* chunk, Column* column);
};