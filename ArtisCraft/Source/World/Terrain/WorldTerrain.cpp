#include "WorldTerrain.h"

WorldTerrain::WorldTerrain(int seed) : m_mainHeightmap(seed)
{
	m_seed = seed;
}

BlockID WorldTerrain::getBlockAt(int x, int y, int z)
{
	if (y < m_mainHeightmap.GetHeight(x, z)) {
		return BlockID::Grass;
	}

	return BlockID::Air;
}