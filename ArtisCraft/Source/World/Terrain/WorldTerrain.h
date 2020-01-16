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

	void buildChunk(Chunk* chunk);

private:
	NoiseWrapper m_mainHeightmap;
	int m_seed;
	
	bool shouldBuild(Chunk* chunk);
};