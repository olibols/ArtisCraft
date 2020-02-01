#include "StructureBuilder.h"

void StructureBuilder::build(Chunk* chunk)
{
	for (auto& block : m_blocks) {
		chunk->setBlock(block.x, block.y, block.z, block.block);
	}
	m_blocks.clear();
}

void StructureBuilder::addBlock(int x, int y, int z, BlockID block)
{
	m_blocks.emplace_back(block, x, y, z);
}

void StructureBuilder::addColumn(int startX, int startY, int startZ, int height, BlockID block)
{
	for (int y = 0; y < height; y++) {
		m_blocks.emplace_back(block, startX, startY + y, startZ);
	}
}

void StructureBuilder::fill(int startX, int startZ, int y, int endX, int endZ, BlockID block)
{
	for (int x = startX; x < endX; x++)
		for (int z = startZ; z < endZ; z++)
			addBlock(x, y, z, block);
}
