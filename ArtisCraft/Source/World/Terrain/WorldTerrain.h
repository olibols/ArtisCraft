#pragma once

#include "../BlockID.h"
#include "Generators/NoiseWrapper.h"

class WorldTerrain {
public:
	WorldTerrain(int seed);

	BlockID getBlockAt(int x, int y, int z);

private:
	NoiseWrapper m_mainHeightmap;

	int m_seed;
};