#pragma once

#include "../BlockID.h"
#include "../Chunk/Chunk.h"

#include <vector>

struct BuilderBlock {
	BuilderBlock(BlockID block, int x, int y, int z) : block(block), x(x), y(y), z(z) {};

	BlockID block;
	int x, y, z;
};

class StructureBuilder {
public:
	StructureBuilder() = default;

	void build(Chunk* chunk);

	void addBlock(int x, int y, int z, BlockID block);
	void addCube(int x, int y, int z, int radius, BlockID block);
	void addColumn(int startX, int startY, int startZ, int height, BlockID block);
	void fill(int startX, int startZ, int startY, int endX, int endZ, int endY, BlockID block);
private:
	std::vector<BuilderBlock> m_blocks;
};