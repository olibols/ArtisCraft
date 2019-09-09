#include "StructureBuilder.h"
#include "../Chunk/Region.h"


void StructureBuilder::build(Region & region)
{
	for (auto& block : _blocks) {
		region.setBlock(block.x, block.y, block.z, block.block);
	}

}

void StructureBuilder::addBlock(int x, int y, int z, BlockID block)
{
	_blocks.emplace_back(block, x, y, z);
}

//(int y, int xStart, int xEnd, int zStart, int zEnd, BlockId block)

void StructureBuilder::fill(int startX, int startZ, int y, int endX, int endZ, BlockID block)
{
	for (int x = startX; x < endX; x++)
		for (int z = startZ; z < endZ; z++)
			addBlock(x, y, z, block);
}

void StructureBuilder::addColumn(int startX, int startY, int startZ, int height, BlockID block)
{
	for (int y = 0; y < height; y++) {
		_blocks.emplace_back(block, startX, startY + y, startZ);
	}
}
