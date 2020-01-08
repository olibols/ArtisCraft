#include "WorldTerrain.h"

BlockID WorldTerrain::getBlockAt(int x, int y, int z)
{
	if (y < 1) {
		return BlockID::Grass;
	}

	return BlockID::Air;
}