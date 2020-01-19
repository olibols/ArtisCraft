#pragma once

#include "../BlockID.h"
#include "Generators/NoiseWrapper.h"

#include "../Coordinates.h"

class Chunk;
struct GenResults;

class WorldTerrain {
public:
	WorldTerrain(int seed);

	BlockID getBlockAt(int x, int y, int z);
	int getHeightAt(int x, int z);

	void buildChunk(Chunk* chunk);

private:
	void setupGens();

	NoiseWrapper m_mainHeightmap;
	NoiseWrapper m_mountainHeightmap;
	int m_seed;
	
	bool shouldBuild(Chunk* chunk);
};