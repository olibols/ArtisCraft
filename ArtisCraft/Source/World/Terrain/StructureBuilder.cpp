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

void StructureBuilder::addCube(int x, int y, int z, int radius, BlockID block)
{
	for (int nx = x - radius; nx < x + radius; nx++) {
		for (int ny = y - radius; ny < y + radius; ny++) {
			for (int nz = z - radius; nz < z + radius; nz++) {
				m_blocks.emplace_back(block, nx, ny, nz);
			}
		}
	}
}

void StructureBuilder::addColumn(int startX, int startY, int startZ, int height, BlockID block)
{
	for (int y = 0; y < height; y++) {
		m_blocks.emplace_back(block, startX, startY + y, startZ);
	}
}

void StructureBuilder::fill(int startX, int startZ, int startY, int endX, int endZ, int endY, BlockID block)
{
	for (int x = startX; x < endX; x++)
		for (int z = startZ; z < endZ; z++)
			for (int y = startY; y < endY; y++)
			addBlock(x, y, z, block);
}

void StructureBuilder::addSphere(int startX, int startY, int startZ, int radius, BlockID block)
{
	for (int x = startX - radius; x < startX + radius; x++)
	for (int y = startY - radius; y < startY + radius; y++)
	for (int z = startZ - radius; z < startZ + radius; z++) {
		if (glm::length(glm::vec3(startX, startY, startZ) - glm::vec3(x, y, z)) < radius) {
			addBlock(x, y, z, block);
		}
	}
}
