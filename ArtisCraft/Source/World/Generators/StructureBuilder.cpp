#include "StructureBuilder.h"
#include "../Chunk/Region.h"


StructureBuilder::StructureBuilder()
{
	
}

void StructureBuilder::build(Region & region)
{
	for (auto block : _blocks) {
		region.setBlock(block.x, block.y, block.z, block.block);
	}

}

void StructureBuilder::addColumn(int startX, int startY, int startZ, int height)
{
	for (int y = 0; y < height; y++) {
		_blocks.emplace_back(BlockID::Wood, startX, startY + y, startZ);
	}
}

void StructureBuilder::fillXZ(int startX, int y, int startZ, int endX, int endZ)
{
}
